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
<img width="1280" height="534" alt="circuit_diagram_senthilkumarank" src="https://github.com/user-attachments/assets/75e48261-fa79-477d-b102-d75d1ed44dac" />
