import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

try:
    df = pd.read_csv('orbit.csv', delimiter=', ', engine='python')
except:
    df = pd.reac_csv('orbit.csv', names=['t', 'x', 'y', 'vx', 'vy'])

plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(0, 0, 'ro', markersize=10, label='Sun')
plt.plot(df['x'], df['y'], label='Earth Orbit')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Orbital Trajectory (Real Space)')
plt.axis('equal')
plt.grid(True)
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(df['x'], df['vx'], color='purple')
plt.xlabel('Position x')
plt.ylabel('Velocity vx')
plt.title('Phase Space (x - vx)')
plt.grid(True)

plt.tight_layout()
plt.show()
