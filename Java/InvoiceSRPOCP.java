// InvoiceSRPOCP.java
// Messy starter: Monolith Invoice Service (violates SRP + OCP)

import java.util.*;
import java.io.*;
import java.math.*;

class LineItem {
    String sku;
    int quantity;
    double unitPrice;

    LineItem(String sku, int quantity, double unitPrice) {
        this.sku = sku;
        this.quantity = quantity;
        this.unitPrice = unitPrice;
    }
}

class InvoiceService {
    // TO FIX (SRP): Does pricing, discounting, tax, rendering, email, logging.
    // TO FIX (OCP): Discount types hard-coded with if/else.
    String process(List<LineItem> items, Map<String, Double> discounts, String email) {
        // pricing
        double subtotal = 0.0;
        for (LineItem it : items) subtotal += it.unitPrice * it.quantity;

        // discounts (tightly coupled)
        double discountTotal = 0.0;
        for (Map.Entry<String, Double> e : discounts.entrySet()) {
            String k = e.getKey();
            double v = e.getValue();
            if (k.equals("percent_off")) {
                discountTotal += subtotal * (v / 100.0);
            } else if (k.equals("flat_off")) {
                discountTotal += v;
            } else {
                // unknown ignored
            }
        }

        // tax inline
        double tax = (subtotal - discountTotal) * 0.18;
        double grand = subtotal - discountTotal + tax;

        // rendering inline (pretend PDF)
        StringBuilder pdf = new StringBuilder();
        pdf.append("INVOICE\n");
        for (LineItem it : items) {
            pdf.append(it.sku).append(" x").append(it.quantity).append(" @ ").append(it.unitPrice).append("\n");
        }
        pdf.append("Subtotal: ").append(subtotal).append("\n")
           .append("Discounts: ").append(discountTotal).append("\n")
           .append("Tax: ").append(tax).append("\n")
           .append("Total: ").append(grand).append("\n");

        // email I/O inline (tight coupling)
        if (email != null && !email.isEmpty()) {
            System.out.println("[SMTP] Sending invoice to " + email + "...");
        }

        // logging inline
        System.out.println("[LOG] Invoice processed for " + email + " total=" + grand);

        return pdf.toString();
    }

    // helper used by ad-hoc tests; also messy on purpose
    double computeTotal(List<LineItem> items, Map<String, Double> discounts) {
        String rendered = process(items, discounts, "noreply@example.com");
        int idx = rendered.lastIndexOf("Total:");
        if (idx < 0) throw new RuntimeException("No total");
        String num = rendered.substring(idx + 6).trim();
        return Double.parseDouble(num);
    }
}

public class InvoiceSRPOCP {
    public static void main(String[] args) {
        InvoiceService svc = new InvoiceService();
        List<LineItem> items = Arrays.asList(
            new LineItem("BOOK-001", 2, 500.0),
            new LineItem("USB-DRIVE", 1, 799.0)
        );
        Map<String, Double> discounts = new HashMap<>();
        discounts.put("percent_off", 10.0);
        System.out.println(svc.process(items, discounts, "customer@example.com"));
    }
}
