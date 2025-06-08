import pandas as pd
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv('pi_convergence.csv')

# ==============================
# Plot 1: Pi Estimate vs Step Size
# ==============================
plt.figure(figsize=(8, 5))
plt.plot(df['step_size'], df['pi_estimate'], marker='o', linestyle='-', color='blue')
plt.axhline(y=3.141592653589793, color='red', linestyle='--', label='True Pi')

plt.title("Estimated Pi vs Step Size", fontsize=14)
plt.xlabel("Step Size (h)", fontsize=12)
plt.ylabel("Estimated Pi", fontsize=12)
plt.xscale('log')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('pi_estimate_plot.png', dpi=300)
plt.show(block=False)  # Show non-blocking so next plot can open too


# ==============================
# Plot 2: Error vs Step Size
# ==============================
plt.figure(figsize=(8, 5))
plt.plot(df['step_size'], df['error'], marker='s', linestyle='-', color='firebrick')

plt.title("Error in Pi Estimation vs Step Size", fontsize=14)
plt.xlabel("Step Size (h)", fontsize=12)
plt.ylabel("Error (|Estimate - True Pi|)", fontsize=12)
plt.xscale('log')
plt.yscale('log')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig('pi_error_plot.png', dpi=300)
plt.show()