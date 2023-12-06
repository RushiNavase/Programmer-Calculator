# Programmer-Calculator Using STM32 Blue pill board
Programmer calculator for arithmetic and Number Conversion 
Hardware Required:STM32F103C8T6 Development board,4x4 Keypad,16x2 Display,Jumper wires and Breadboard.
Software:STM32cubeIDE/Keil u Vision
# code workFlow and Functionality overview:
LCD Functions:
   - The code includes functions (`lcd_cmd`, `lcd_data`, `lcd_string`, and `lcd_init`) to interact with an LCD display. These functions handle sending commands, data, and initializing the LCD.

Button Matrix Functions:
   - The code contains functions (`check_R1`, `check_R2`, `check_R3`, `check_R4`, `key_Press`) to read input from a 4x4 button matrix.

Calculator and Converter Logic:
   - The `main` function initializes the system, sets up the GPIO, and enters an infinite loop for the main functionality.
   - The user is prompted to select either a calculator or a converter.
    
  Calculator Functionality:
     The user is prompted to enter the first number, operation, and the second number.
     Arithmetic operations (addition, subtraction, multiplication, and division) are performed, and the result is displayed on the LCD.
   - Addition (`A` on the keypad)
   - Subtraction (`B` on the keypad)
   - Multiplication (`C` on the keypad)
   - Division (`D` on the keypad)
 
  Converter Functionality:
     The user is prompted to choose between different conversion options (binary to decimal, decimal to binary, decimal to hexadecimal, hexadecimal to decimal).
     The selected conversion is performed based on user input.
   - Binary to Decimal (`1` on the keypad)
   - Decimal to Binary (`2` on the keypad)
   - Decimal to Hexadecimal (`3` on the keypad)
   - Hexadecimal to Decimal (`4` on the keypad)

      - The `*` button serves as a clear button, allowing the user to start over.
      - The `#` button acts as an input confirmation, moving to the next step or performing the calculation.

 User Interface:
   - The LCD is used to display prompts, numbers, and results.
   - The user interacts with the system through a 4x4 button matrix.
   - The `*` button is used as a clear button to reset inputs.
   - The `#` button serves as an input confirmation, allowing the user to proceed with the entered data.



