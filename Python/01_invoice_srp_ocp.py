# 01-invoice-srp-ocp.py
from typing import List, Dict
from dataclasses import dataclass

@dataclass
class LineItem:
    sku: str
    quantity: int = 0
    unit_price: float = 0.0

class InvoiceService:
    def process(self, items: List[LineItem], discounts: Dict[str, float], email: str) -> str:
        # pricing
        subtotal = 0.0
        for item in items:
            subtotal += item.unit_price * item.quantity

        # discounts (tightly coupled)
        discount_total = 0.0
        for discount_type, value in discounts.items():
            if discount_type == "percent_off":
                discount_total += subtotal * (value / 100.0)
            elif discount_type == "flat_off":
                discount_total += value
            else:
                # unknown ignored
                pass

        # tax inline
        tax = (subtotal - discount_total) * 0.18
        grand = subtotal - discount_total + tax

        # rendering inline (pretend PDF)
        pdf_lines = ["INVOICE"]
        for item in items:
            pdf_lines.append(f"{item.sku} x{item.quantity} @ {item.unit_price}")
        
        pdf_lines.extend([
            f"Subtotal: {subtotal}",
            f"Discounts: {discount_total}",
            f"Tax: {tax}",
            f"Total: {grand}"
        ])
        
        pdf_content = "\n".join(pdf_lines)

        # email I/O inline (tight coupling)
        if email:
            print(f"[SMTP] Sending invoice to {email}...")

        # logging inline
        print(f"[LOG] Invoice processed for {email} total={grand}")

        return pdf_content

    # helper used by ad-hoc tests; also messy on purpose
    def compute_total(self, items: List[LineItem], discounts: Dict[str, float]) -> float:
        dummy_email = "noreply@example.com"
        rendered = self.process(items, discounts, dummy_email)
        
        # Find total line
        lines = rendered.split('\n')
        for line in lines:
            if line.startswith("Total:"):
                return float(line.split(":")[1].strip())
        raise RuntimeError("No total found")

def main():
    svc = InvoiceService()
    
    # Create items
    items = [
        LineItem("ITEM-001", 3, 100.0),
        LineItem("ITEM-002", 1, 250.0)
    ]
    discounts = {"percent_off": 10.0}
    
    print(svc.process(items, discounts, "customer@example.com"))

if __name__ == "__main__":
    main()