# Dual DC Motor Position Control Using PID and Encoder Feedback

## Documentation

### Summary of Approach
This project implements **closed-loop position control of two DC motors** using optical rotary encoders for feedback, driven via an **L293 motor driver** and an **Arduino Uno**. 

The control logic is based on a **Proportional-Integral-Derivative (PID)** algorithm, which continuously calculates the error between the motor’s current position (from encoder counts) and a desired setpoint, then adjusts motor output to minimize this error. 

The system is designed to be **responsive and precise**, allowing the motors to stop accurately at their target positions.

---

### Key Implementation Features

- **Encoder Integration:**  
  Both motors are fitted with encoders, with their A channels wired to Arduino interrupt pins. This ensures real-time, accurate position tracking even at high speeds.

- **PID Control:**  
  The PID algorithm is executed every 50ms for each motor, providing smooth and accurate convergence to the target position. Gains (**Kp, Ki, Kd**) are tunable in code.

- **Flexible Setpoint Inputs:**  
  Users can change the target position using physical pushbuttons (increment/decrement by fixed steps) or by sending a Serial command from a connected PC.

- **User Feedback:**  
  Key variables (position, setpoint, error, and status) are printed to the serial monitor every cycle for transparency and tuning.  
  An onboard LED indicates when both motors have accurately reached their targets.

---

### Assumptions

- Motor encoders generate clean quadrature signals suitable for hardware interrupt counting.
- Motors are sufficiently responsive for the given PID parameters and will stop reliably within the set deadband.
- The Arduino Uno has sufficient performance for the PID loop (tested with 50ms interval).

---

### Improvements Over Baseline

- Dynamic setpoint updates via both hardware (buttons) and software (Serial).
- Target-reached LED visual indicator.
- Debounced button handling.
- Modular design for clarity and maintainability.

---

### Notes on Tweaks, Extensions, and Customization

**Setpoint Input Methods:**  
Besides having a fixed setpoint in code, real-time setpoint updates are enabled via pushbuttons and by entering commands through the Serial monitor (e.g., `S1200,900`).

**Feedback/Indicators:**  
An LED (connected to A2) provides instant visual feedback when both motors reach their setpoints within a defined error threshold.

**PID Parameter Tuning:**  
Gains for **Kp, Ki, and Kd** were adjusted experimentally for optimal response—quick movement to the target with minimal overshoot.

**Button Debounce:**  
A software debounce routine is implemented for both increment and decrement buttons to ensure reliable input without false triggering.

**Serial Monitoring Enhancements:**  
Additional information such as setpoint, error, and "At Target" status is output each loop cycle, making real-time testing and tuning easier.

**Scalability:**  
The code structure can easily be expanded for additional motors or other sensor types, owing to the modular function breakdown and flexible setpoint architecture.

---

### Potential Extensions

- **Current sensing** (using A0/A1 ports, currently reserved).
- Addition of a **buzzer**, **safety lockout**, or **Bluetooth remote input** for further usability.
- **Data logging** for plotting system performance offline.

---

### Conclusion
This implementation offers **accurate, dynamic, and user-friendly dual-motor position control**, demonstrating a practical application of feedback control principles using affordable hardware.
