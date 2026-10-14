# Arduino Ultrasonic Hand-Following Robot Car 🚗

A step-by-step robotics project for students using an Arduino Uno, L298N motor driver, four DC motors, an HC-SR04 ultrasonic sensor, and an SG90 servo motor.

## 🎯 Project Objective

Build a four-wheel robot car that uses an ultrasonic sensor to detect nearby objects, scan left and right, and respond to a target's distance.

**Suitable for:** School robotics labs, STEM learning, Arduino practice, and robotics competitions.

## 🧰 1. Required Components

| No. | Component | Quantity |
|---|---|---:|
| 1 | Arduino Uno compatible board | 1 |
| 2 | L298N dual H-bridge motor driver | 1 |
| 3 | HC-SR04 ultrasonic sensor | 1 |
| 4 | SG90 9g servo motor | 1 |
| 5 | DC geared motors | 4 |
| 6 | Robot chassis with four wheels | 1 |
| 7 | Suitable motor battery pack | 1 |
| 8 | Regulated 5V servo supply, if needed | 1 |
| 9 | Jumper wires | As needed |
| 10 | USB cable for Arduino | 1 |

## ⚙️ 2. How the Robot Works

- **Arduino Uno:** Controls the robot.
- **L298N:** Controls the direction and speed of the motors.
- **Ultrasonic sensor:** Measures the distance to nearby objects.
- **Servo motor:** Rotates the sensor to scan different directions.
- **Four DC motors:** Move the robot forward, backward, and turn.

The four motors are divided into two groups:

- Left-side motors → L298N motor channel A.
- Right-side motors → L298N motor channel B.

> Important: Confirm that the combined current of the two motors on each side is within the driver's limits. Four motors can draw substantial current, especially when starting or stalled.

## 🔌 3. Connect the Four Motors

**Disconnect the battery and USB cable before wiring.**

| L298N output | Motor connection |
|---|---|
| OUT1 and OUT2 | Both left-side motors, connected in parallel |
| OUT3 and OUT4 | Both right-side motors, connected in parallel |

Connect the two motors on each side so they rotate in the same direction when the robot is commanded to move forward.

If one motor rotates in the wrong direction, disconnect the power and reverse that motor's two wires.

## 🔗 4. Connect the L298N to Arduino Uno

Use this pin configuration:

| L298N pin | Arduino Uno pin |
|---|---|
| ENA | D5 |
| IN1 | D8 |
| IN2 | D9 |
| IN3 | D10 |
| IN4 | D11 |
| ENB | D6 |
| GND | GND |

**Speed control:** Remove the ENA and ENB jumpers if fitted, then connect ENA to D5 and ENB to D6.

These Arduino pins support PWM speed control.

Check the labels on your actual motor-driver board before connecting wires.

## 📡 5. Connect the HC-SR04 Ultrasonic Sensor

| HC-SR04 pin | Arduino Uno pin |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D12 |
| ECHO | D13 |

Mount the sensor on the servo horn, facing forward. Leave enough wire slack for the sensor to rotate without pulling its connections.

## 🔄 6. Connect the SG90 Servo Motor

| Servo wire | Connection |
|---|---|
| Signal, commonly orange/yellow | Arduino D3 |
| Power, commonly red | Suitable regulated 5V supply |
| Ground, commonly brown/black | Common GND |

Wire colours can vary, so verify your servo's connections.

For reliable operation, use a suitable regulated 5V supply for the servo rather than relying on the Arduino's 5V output under load.

**Important:** Connect the external servo supply's GND to Arduino GND.

## 🔋 7. Connect the Power Supply

1. Connect motor battery positive (+) to the L298N motor power input, commonly marked `12V` or `+12V`.
2. Connect motor battery negative (−) to L298N GND.
3. Connect Arduino GND, L298N GND, sensor GND, and servo supply GND together.
4. Power the Arduino using USB during programming.
5. Check every connection before switching on the battery.

### ⚠️ Power Safety

- Never connect the motor battery directly to Arduino 5V.
- Never power the motors through the Arduino's 5V pin.
- Do not assume the L298N's 5V terminal is always an output; its function depends on the board's regulator and jumper configuration.
- Use a battery voltage appropriate for the motors and driver.
- Check polarity before powering the circuit.
- Keep the wheels raised during the first motor test.
- Disconnect all power before changing wires.

## 💻 8. Upload the Arduino Program

The Arduino sketch should be named `robot_car.ino`.

### Steps

1. Install and open Arduino IDE.
2. Open `robot_car.ino`.
3. Connect the Arduino Uno using a USB cable.
4. Select **Tools → Board → Arduino Uno**.
5. Select the correct port under **Tools → Port**.
6. Click **Verify** to compile the program.
7. Click **Upload** to transfer the program.
8. Open **Tools → Serial Monitor** and select `9600 baud` if the sketch uses that setting.

The program uses the standard Arduino `Servo` library. Install it through the Arduino IDE Library Manager if required.

**Repository files:** Make sure you upload both `README.md` and `robot_car.ino`. This README is the build guide; it does not contain the actual Arduino sketch.

## 🧪 9. Student Testing Checklist

Complete each test before moving to the next.

- [ ] Inspect all wiring with the power disconnected.
- [ ] Raise the wheels clear of the table.
- [ ] Switch on the motor supply.
- [ ] Test the left-side motors.
- [ ] Test the right-side motors.
- [ ] Confirm both sides rotate in the intended forward direction.
- [ ] Confirm the servo turns the sensor left and right.
- [ ] Open Serial Monitor and check distance readings.
- [ ] Place a hand in front of the sensor and observe the response.
- [ ] Test the car at low speed on a clear floor.
- [ ] Repeat the tests before competition day.

## 🛠️ 10. Troubleshooting

| Problem | Possible cause | Solution |
|---|---|---|
| One side moves backward | Motor wires are reversed | Reverse the affected motor connections with power disconnected |
| Motors do not move | Missing motor power or incorrect enable wiring | Check the battery, ENA/ENB connections, and motor outputs |
| Servo jitters | Insufficient power | Use a suitable regulated 5V supply |
| Arduino resets when motors start | Voltage drop or electrical interference | Check battery capacity, grounding, and power wiring |
| No distance readings | Incorrect TRIG/ECHO wiring | Check D12, D13, 5V, and GND |
| Robot turns the wrong way | Motor grouping or code direction issue | Check left/right connections and direction logic |
| Sensor hits the chassis | Poor mounting or wire routing | Reposition the sensor and allow free rotation |

## 🏆 11. Competition Preparation

Before the competition, test and tune:

- Target-following distance.
- Servo scanning angles.
- Turning response.
- Stopping distance.
- Motor speed.
- Battery endurance.
- Performance on the actual competition surface.

Remember that an ultrasonic sensor measures distance. It does **not** recognize a human hand. Another object at a similar distance may trigger the same behaviour.

The four motors, battery voltage, wheel friction, and chassis weight affect how the car moves. Students should test and adjust the program on the completed robot rather than relying on one fixed set of timing values.

## 📁 12. Recommended GitHub Structure

```text
arduino-ultrasonic-robot-car/
├── README.md
├── robot_car.ino
└── images/
    ├── wiring-overview.png
    └── completed-robot.jpg
```

You can add your own wiring diagram and photographs to the `images` folder.

To display a wiring image in this README, use:

```markdown
![Robot wiring overview](images/wiring-overview.png)
```

## 👨‍🏫 13. Student Learning Outcomes

After completing this project, students should be able to:

- Identify Arduino Uno pins and connections.
- Understand motor-driver control.
- Connect and operate DC motors.
- Read distance measurements from an ultrasonic sensor.
- Control a servo motor.
- Follow safe wiring and testing procedures.
- Debug basic hardware problems.
- Prepare a robot for a STEM competition.

## 🔒 Safety Reminder

Build and test the robot under adult supervision. Keep fingers, loose wires, hair, and clothing away from moving wheels and gears. Disconnect the battery before adjusting the wiring or working on the chassis.

---

**Project:** Arduino Ultrasonic Hand-Following Robot Car  
**Platform:** Arduino Uno  
**Programming language:** Arduino C++  
**Purpose:** Robotics education and STEM competition preparation
