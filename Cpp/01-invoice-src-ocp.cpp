
// 01-invoice-srp-ocp.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

/*
process function:

    first it is finding subtotal, then finding discount, then finding tax by removing the disc..

    then it prints all the items that have been bought and other info including subtotal,disc..

    email is also sent here only using string email..

    so Responsibility of InvoiceService should be only 1..

    currently the responsibilities are :

    1) tax calculation. ( i removed that..)

    2) applying the type of discount. (separate class created for this as well..)

    3) sum calculation ( i dont think that this one needs to be done with some diff class because it is always going to be just addition)

    4) printing .. this also can have diff methods.., currently it uses PDF with

    now the discount part is done..

    now we need to implement the printing part..

    so we will create the type of printing that we need , we can do it with one of these 2 ways :

    i) create a factory to dynamically create the type on the basis of input .

    ii) just create a type of our choice in main()..





*/
struct LineItem
{
    string sku;
    int quantity{0};
    double unitPrice{0.0};
};
class TaxCalculator
{
public:
    virtual double taxFinder(double amount) = 0;
};
class IndiaTaxCalculator : public TaxCalculator
{
public:
    double taxFinder(double amount) override
    {
        return 0.18 * amount;
    }
};
class USATaxCalculator : public TaxCalculator
{
public:
    double taxFinder(double amount) override
    {
        return 0.10 * amount;
    }
};
class Discount
{
public:
    virtual double apply(double subtotal) = 0;
};
class FlatDiscount : public Discount
{
public:
    FlatDiscount(double discount_) : discount(discount_) {};
    double apply(double subtotal) override
    {
        return discount;
    }

private:
    double discount;
};
class PercentDiscount : public Discount
{
public:
    PercentDiscount(double percent_) : percent(percent_) {};
    double apply(double subtotal) override
    {
        return (subtotal * (percent / 100.0));
    }

private:
    double percent;
};
class InvoiceRenderer
{
public:
    virtual string render(const vector<LineItem> &items_, double subTotal_, double discount_, double tax_, double grand_) = 0;
};
class PdfRenderer : public InvoiceRenderer
{
public:
    PdfRenderer() {}

    string render(const vector<LineItem> &items, double subTotal, double discount, double tax, double grand) override
    {
        // rendering inline (pretend PDF)
        ostringstream pdf;
        pdf << "INVOICE\n";
        for (auto &it : items)
        {
            pdf << it.sku << " x" << it.quantity << " @ " << it.unitPrice << "\n";
        }
        pdf << "Subtotal: " << subTotal << "\n"
            << "Discounts: " << discount << "\n"
            << "Tax: " << tax << "\n"
            << "Total: " << grand << "\n";
        return pdf.str();
    }
};

class InvoiceService
{
public:
    string process(const vector<LineItem> &items,
                   const vector<Discount *> &discounts,
                   const string &email, InvoiceRenderer *renderer)
    {
        // pricing
        double subtotal = 0.0;
        for (auto &it : items)
            subtotal += it.unitPrice * it.quantity;

        // discounts (tightly coupled)
        double discount_total = 0.0;
        for (auto &kv : discounts)
        {
            discount_total += kv->apply(subtotal);
        }

        // tax inline
        double tax = (subtotal - discount_total) * 0.18;
        double grand = subtotal - discount_total + tax;
        string res = renderer->render(items, subtotal, discount_total, tax, grand);

        // email I/O inline (tight coupling)
        if (!email.empty())
        {
            cout << "[SMTP] Sending invoice to " << email << "...\n";
        }

        // logging inline
        cout << "[LOG] Invoice processed for " << email << " total=" << grand << "\n";
        return res;
    }

    // helper used by ad-hoc tests; also messy on purpose
    double computeTotal(const vector<LineItem> &items,
                        const vector<Discount *> &discounts, InvoiceRenderer *renderer)
    {
        string dummyEmail = "noreply@example.com";
        auto rendered = process(items, discounts, dummyEmail, renderer);
        auto pos = rendered.rfind("Total:");
        if (pos == string::npos)
            throw runtime_error("No total");
        auto line = rendered.substr(pos + 6);
        return stod(line);
    }
};
class DiscountFactory
{
public:
    static Discount *create(string type, double val)
    {
        if (type == "percent_off")
        {
            return new PercentDiscount(val);
        }
        else if (type == "flat_off")
        {
            return new FlatDiscount(val);
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    InvoiceService svc;
    // Create items
    vector<LineItem> items = {{"ITEM-001", 3, 100.0}, {"ITEM-002", 1, 250.0}};
    map<string, double> Discounts = {{"percent_off", 10.0}};
    vector<Discount *> discounts;
    DiscountFactory discountFactory;
    for (auto &a : Discounts)
    {
        string type = a.first;
        double val = a.second;
        discounts.push_back(discountFactory.create(type, val));
    }
    InvoiceRenderer *renderer = new PdfRenderer();

    cout << svc.process(items, discounts, "customer@example.com", renderer) << endl;
    return 0;
}
