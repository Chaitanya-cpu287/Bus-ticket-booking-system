# Smart-RTC: Automated Bus Ticketing System

A terminal-based application designed for Road Transport Corporations to automate ticket issuance and daily financial reporting. This project was developed to demonstrate core Object-Oriented Programming (OOP) concepts and practical file handling in C++.

## 🌟 Features
- **Automated Fare Engine:** Calculates ticket prices based on distance with precision formatting.
- **Dual-Mode Persistence:** - **Visual Receipts:** Generates a structured ASCII "Box" ticket in `receipt.txt`.
    - **Audit Logs:** Appends transaction data to `ticket_history.csv` for Excel compatibility.
- **Waybill Management:** Tracks total sales and ticket counts for a driver's shift summary.
- **User-Centric Formatting:** Uses the `<iomanip>` library to ensure a clean UI/UX in the terminal.

## 🛠️ Concepts Demonstrated
- **Encapsulation:** Using private data members to protect sensitive financial data.
- **Classes & Objects:** Modular design separating Ticket logic from Waybill (summary) logic.
- **File I/O:** Using `ofstream` for both overwriting (receipts) and appending (logs).
- **Static State Management:** Handling staff IDs and depot information across multiple tickets.

## 📂 File Structure
- `main.cpp`: Contains the complete source code.
- `receipt.txt`: The most recently generated passenger ticket.
- `ticket_history.csv`: A permanent log of all tickets sold (ready for data analysis).

## 🚀 Getting Started
1. **Compile:**
   ```bash
   g++ main.cpp -o SmartRTC