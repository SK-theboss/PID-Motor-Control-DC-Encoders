# PID-Motor-Control-DC-Encoders
Dual DC Motor PID Position Control using Encoders, Arduino, and L293D.

## Project Overview

This project demonstrates **precise position control of two DC motors** using a **PID (Proportional-Integral-Derivative) control algorithm** on an **Arduino UNO**. Rotary encoders provide real-time feedback on motor positions, and the motor speed and direction are managed through an **L293D motor driver IC**.

The system allows dynamic setpoint adjustments via onboard buttons, and a visual indicator (LED) shows when both motors have reached their target positions.

---

## Features
- **Dual PID Control Loops:** Independent PID for each motor.
- **Rotary Encoder Feedback:** For accurate position tracking.
- **Dynamic Setpoint Adjustment:** Via pushbuttons or Serial Monitor.
- **Visual Feedback:** LED indicator when both motors reach their respective setpoints.
- **Real-Time Serial Monitoring:** Displays encoder counts, errors, and status.

---

## Components Used
| Component                 | Quantity |
|---------------------------|----------|
| Arduino UNO               | 1        |
| DC Motors with Encoder    | 2        |
| L293D Motor Driver IC     | 1        |
| Pushbuttons               | 2        |
| LED + Resistor (220Ω)     | 1        |
| Breadboard & Jumper Wires | As needed|
| Power Supply (9V-12V)     | 1        |

---
## Circuit Diagram
<img width="1280" height="534" alt="circuit_diagram_senthilkumarank" src="https://github.com/user-attachments/assets/e7480bde-d88a-4a18-9200-fa79e6db29c2" />

## Outputs
<img width="1920" height="1129" alt="output" src="https://github.com/user-attachments/assets/a9425f72-f7b4-434b-8c55-177d457ef2d6" />

Video Link:
https://drive.google.com/file/d/1ZP5Iaj4Nf5-DhFtm1_kYQE4Od7PKr4X2/view?usp=sharing


