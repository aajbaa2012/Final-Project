//-----------------------------------------------------------------------
//Name:  - Senior Design Project of Counting the Crowd entering the
//	   Jamaraat area during the Hajj.
//       - PIC16F628a#1 is uesd as a storage unit to store and sent the
//         calculated echo pulses of Ultrasonic sensor to the Arduino 
//         Uno R3.
//       - Assuming a room temp of 25 degrees centigrade.
//Autor:   Ahmed Abdulaziz Abualsaud
//Version: v 1.0
//Date:    Dec, 2, 2015
//-----------------------------------------------------------------------

void main()
{
     //Declare teh Global Variable
     int a;       //Variable to store the echo pulses
     int i = 1;   //Counter to know which sensor is selected
     char txt[7]; //Char String is used to send the distance to the Arduino
     char txtD[7];//Char String is used to send the selected sensor to the Arduino
     
     //Configure all pin as digital by disable the comparators
     CMCON = 0b00000111;
     
     //Configure the TIMER1 to work beasd on the internal oscilator speed 4MHz
     T1CON = 0b00000000;

     //Configure each digital bins as In/Out ports
     //Pin Name  - 0/1        - Pin Lable    - Pin Number
     TRISA.F0    = 0;//       = exP1         - 17
     TRISA.F1    = 0;//       = stP1         - 18
     TRISA.F4    = 1;//       = done         - 3
     TRISB.F1    = 1;//       = Read1        - 7
     TRISB.F2    = 0;//       = MX1          - 8
     TRISB.F4    = 1;//       = C            - 10
     TRISB.F5    = 1;//       = D            - 11

     UART1_Init(9600);// Initialize UART module at 9600 bps
     Delay_ms(50);    // Wait for UART module to stabilize

     while (1)
     {
           //Clear the TIMER1 registers
           TMR1H = 0;
           TMR1L = 0;
           PORTA.F0 = 0;               //Disable exP1 signal
           PORTA.F1 = 0;               //Disable stP1 signal

           while(!PORTB.F1);           //Wait the echo (Read1 signal) to become 1
           T1CON.F0 = 1;               //Enable the TIMER1
           while(PORTB.F1);
           T1CON.F0 = 0;
           
           a = (TMR1L | (TMR1H << 8)) / 29.1 / 2;//Calculate the distance
           //Convert the distance data and sensor number from integer to string
           IntToStr(a,txt);
           Ltrim(txt);
           IntToStr(i,txtD);
           Ltrim(txtD);
           
           //Wait the control Signal from Arduino to start sending the data
           while(PORTB.F5 != 0 && PORTB.F4 != 0);//D&C
           
           PORTA.F1 = 1;               //Enable stP1 signal
           
           // Start sending data via UART
           UART1_Write_Text("GG1_");
           UART1_Write_Text(txtD);
           UART1_Write_Text(": ");
           UART1_Write_Text(txt);
           UART1_Write_Text(" cm");
           UART1_Write_Text("!");
           UART1_Write(13);            // The Carriage Return
           
           PORTA.F0 = 1;               //Enable exP1 Signal

           ++i;                        //Increment the sensor iterator
           if (i == 5){i = 1;}         //Reset the sensor iterator
           while(PORTA.F4 == 0);       //Wait for the done signal coming from Arduino
     }//End while loop
}//End void main
