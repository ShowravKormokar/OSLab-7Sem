import tkinter as tk
from tkinter import messagebox, ttk

class SchedulerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("FCFS Scheduler")
        self.root.configure(bg="skyblue")
        self.process_entries = []

        self.create_widgets()

        # Enable mouse wheel scrolling
        self.canvas.bind_all("<MouseWheel>", lambda e: self.canvas.yview_scroll(int(-1*(e.delta/120)), "units"))

    def create_widgets(self):
        # Main frame with skyblue background
        self.main_frame = tk.Frame(self.root, bg="skyblue")
        self.main_frame.pack(expand=True, fill="both", padx=20, pady=20)

        # Row for entering number of processes
        tk.Label(self.main_frame, text="Number of Processes:", bg="skyblue", fg="black", font=("Arial", 12)).grid(row=0, column=0, padx=5, pady=5, sticky="e")
        self.num_entry = tk.Entry(self.main_frame, bg="white", fg="black", font=("Arial", 12))
        self.num_entry.grid(row=0, column=1, padx=5, pady=5)
        tk.Button(self.main_frame, text="Create Input Fields", command=self.create_input_fields, bg="white", fg="black", font=("Arial", 12)).grid(row=0, column=2, padx=10)

        # Canvas + scrollbar setup for scrollable input area
        self.canvas = tk.Canvas(self.main_frame, bg="skyblue", highlightthickness=0)
        self.canvas.grid(row=1, column=0, columnspan=3, sticky="nsew")

        self.scrollbar = tk.Scrollbar(self.main_frame, orient="vertical", command=self.canvas.yview)
        self.scrollbar.grid(row=1, column=3, sticky="ns")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)

        # Frame inside canvas
        self.input_frame = tk.Frame(self.canvas, bg="skyblue")
        self.canvas.create_window((0, 0), window=self.input_frame, anchor="nw")

        # Update scrollregion when new widgets are added
        self.input_frame.bind("<Configure>", lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all")))

        # Table for output
        self.tree = ttk.Treeview(self.main_frame, columns=("AT", "BT", "CT", "TAT", "WT"), show="headings", height=8)
        for col in ("AT", "BT", "CT", "TAT", "WT"):
            self.tree.heading(col, text=col)
            self.tree.column(col, width=80, anchor="center")
        self.tree.grid(row=2, column=0, columnspan=3, pady=10)

        # Styling the Treeview
        style = ttk.Style()
        style.theme_use("default")
        style.configure("Treeview.Heading", font=("Arial", 11, "bold"))
        style.configure("Treeview", background="white", foreground="black", rowheight=25, fieldbackground="white", font=("Arial", 10))
        style.map('Treeview', background=[('selected', 'lightblue')])

        # Label to show average TAT and WT
        self.avg_label = tk.Label(self.main_frame, text="", bg="skyblue", fg="black", font=("Arial", 12, "bold"))
        self.avg_label.grid(row=3, column=0, columnspan=3, pady=10)

    def create_input_fields(self):
        # Clear previous input fields
        for widget in self.input_frame.winfo_children():
            widget.destroy()

        try:
            num = int(self.num_entry.get())
        except ValueError:
            messagebox.showerror("Error", "Please enter a valid number")
            return

        self.process_entries.clear()

        # Create input fields dynamically for each process
        for i in range(num):
            tk.Label(self.input_frame, text=f"P{i+1} AT:", bg="skyblue", fg="black", font=("Arial", 10)).grid(row=i, column=0, padx=5, pady=2, sticky="e")
            at = tk.Entry(self.input_frame, bg="white", fg="black", font=("Arial", 10))
            at.grid(row=i, column=1, padx=5, pady=2)

            tk.Label(self.input_frame, text="BT:", bg="skyblue", fg="black", font=("Arial", 10)).grid(row=i, column=2, padx=5, pady=2, sticky="e")
            bt = tk.Entry(self.input_frame, bg="white", fg="black", font=("Arial", 10))
            bt.grid(row=i, column=3, padx=5, pady=2)

            self.process_entries.append((at, bt))

        # Run button at the bottom
        tk.Button(self.input_frame, text="Run FCFS", command=self.run_fcfs, bg="white", fg="black", font=("Arial", 11, "bold")).grid(row=num, column=0, columnspan=4, pady=10)

    def run_fcfs(self):
        processes = []
        for i, (at_entry, bt_entry) in enumerate(self.process_entries):
            try:
                at = int(at_entry.get())
                bt = int(bt_entry.get())
                processes.append({"id": i + 1, "arrival": at, "burst": bt})
            except ValueError:
                messagebox.showerror("Error", f"Invalid input for process {i + 1}")
                return

        # Sort by arrival time
        processes.sort(key=lambda x: x["arrival"])
        current_time = 0
        total_tat = total_wt = 0

        for p in processes:
            if current_time < p["arrival"]:
                current_time = p["arrival"]
            p["completion"] = current_time + p["burst"]
            p["turnaround"] = p["completion"] - p["arrival"]
            p["waiting"] = p["turnaround"] - p["burst"]
            current_time = p["completion"]
            total_tat += p["turnaround"]
            total_wt += p["waiting"]

        # Clear previous output
        for row in self.tree.get_children():
            self.tree.delete(row)

        # Insert new output
        for p in processes:
            self.tree.insert("", tk.END, values=(p["arrival"], p["burst"], p["completion"], p["turnaround"], p["waiting"]))

        avg_tat = total_tat / len(processes)
        avg_wt = total_wt / len(processes)

        self.avg_label.config(text=f"Average TAT: {avg_tat:.2f} | Average WT: {avg_wt:.2f}")

# Launch the app
if __name__ == "__main__":
    root = tk.Tk()
    app = SchedulerApp(root)
    root.mainloop()
