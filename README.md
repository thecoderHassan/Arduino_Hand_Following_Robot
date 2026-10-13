# Arduino 4-Wheel Robot — Wiring, Upload & Testing

This project is a starting sketch for the robot shown in the photos: an Arduino Uno, a red dual motor-driver board that appears to be an **L298N**, four DC gear motors/wheels, a servo, and an ultrasonic distance sensor. The sketch provides basic ultrasonic **hand/target following**: keep your hand as the closest object in front of the sensor, and the car approaches or turns toward the detected target.

## Important note about the photos

The photos show the overall components, but the Arduino pin labels and individual wire endpoints are obscured by the wiring. I **cannot confirm the actual pin-to-pin connections from the photos alone**. The sketch therefore uses the suggested wiring below. Match the physical wiring to this table before uploading, or edit the pin constants in `robot_car.ino` to match your existing wiring.

Important limitation: an ultrasonic sensor measures distance; it cannot identify a hand specifically. This is basic target-following, so it may follow another object at a similar distance. Keep the hand as the closest object in view.

## 1. Suggested wiring

### L298N motor driver to Arduino Uno

| L298N label | Arduino Uno |
|---|---|
| ENA | D5 (PWM) |
| IN1 | D8 |
| IN2 | D9 |
| IN3 | D10 |
| IN4 | D11 |
| ENB | D6 (PWM) |
| GND | Arduino GND and battery negative |

- Connect the **left-side two motors in parallel** to OUT1/OUT2.
- Connect the **right-side two motors in parallel** to OUT3/OUT4.
- If the left and right sides are reversed, swap the motor-side connections or change the code.
- Remove the ENA/ENB jumpers only if you are using D5/D6 for speed control. If the jumpers remain installed, PWM speed control may not work as intended.
- Two motors in parallel on each channel can exceed the L298N's current capacity. Check each motor's stall current and the driver's cooling/current limits.

### HC-SR04 ultrasonic sensor

| HC-SR04 pin | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D12 |
| ECHO | D13 |

### Servo

| Servo wire | Connection |
|---|---|
| Signal (often orange/yellow) | D3 |
| VCC (often red) | Regulated 5V supply suitable for the servo |
| GND (often brown/black) | Common GND |

Wire colours vary, so verify the servo's labels/datasheet. A separate regulated 5V supply is often more reliable for the servo than the Uno's 5V pin. **Connect the supply grounds together.**

## 2. Power and safety

- Do **not** power the four motors from the Arduino 5V pin.
- Power the motor driver's motor-supply input from a suitable battery pack for your motors.
- Join Arduino GND, motor-driver GND, sensor GND, and servo-supply GND.
- Check polarity and wiring before switching on. Lift the wheels off the table for the first test.
- Do not connect the motor battery's positive terminal to Arduino 5V.
- The L298N red board in the image looks like a motor driver, not a relay module. If your board is actually a different module, do not use this pin map until the board model is confirmed.

## 3. Upload the code

1. Install/open the Arduino IDE.
2. Open `robot_car.ino`.
3. Connect the Uno using USB.
4. In **Tools → Board**, choose **Arduino Uno**.
5. In **Tools → Port**, select the port for your Uno.
6. Click **Verify** (✓). Then click **Upload** (→).
7. Keep the wheels raised for the first powered test.

The standard Arduino IDE includes the `Servo` library. No additional library should be required for this sketch.

## 4. What the code does

1. Reads the distance in front of the car.
2. Moves forward when a target is detected roughly 18–45 cm ahead.
3. Reverses briefly if the target is closer than 18 cm.
4. If no target is in the forward range, scans left and right with the servo.
5. Turns toward a detected nearby target; if no target is found, stops instead of driving blindly.
6. Prints front, left, and right distance readings in **Tools → Serial Monitor** at **9600 baud**.

## 5. Adjusting behaviour

Near the top of `robot_car.ino`:

- `MOTOR_SPEED`: forward/reverse speed, from 0 to 255.
- `TURN_SPEED`: turning speed, from 0 to 255.
- The follow-distance range is currently 18–45 cm in `loop()`; adjust it for your hand and sensor.
- `TARGET_MAX_CM` in `loop()` controls how far away a target may be when the car searches left/right.
- `SERVO_LEFT`, `SERVO_CENTER`, `SERVO_RIGHT`: sensor scan angles.

If the robot drives backward when it should go forward, the motor polarity or motor-side wiring is reversed. Swap the two wires for the affected motor group, or reverse the relevant HIGH/LOW states in `forward()` and `backward()`.

If the robot turns the wrong way, swap the left/right motor groups or swap the left/right decision in `loop()`.

## 6. Troubleshooting

- **Motors do not move:** check battery voltage, motor-driver power terminals, GND commonality, ENA/ENB jumpers, and the motor output terminals.
- **Uno resets when motors start:** the motor/servo supply may be sagging or noisy. Use a suitable separate supply and common ground.
- **Servo jitters or Uno resets:** use a regulated servo supply with sufficient current; connect grounds together.
- **Distance always reads about 400 cm:** check TRIG/ECHO pins, sensor power, sensor orientation, and wiring.
- **One side spins in the wrong direction:** swap the two motor leads for that side.
- **PWM speed does not change:** check that ENA/ENB are connected to D5/D6 and that the jumpers are removed when required.

## 7. Pin-map reminder

The code cannot know the actual wiring from a photo where the endpoints are hidden. If your wires are already connected to different Uno pins, update the constants at the top of the sketch to match your wiring before uploading.
