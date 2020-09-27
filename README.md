# GLCD-Interface

This was a freelancing project to make an embedded system to control the temperature of a storage facility to store food.

The first phase of the project was to create an interactive system (GLCD with rotary switch) to enable a low technical level user to interact with the system and control it on a higher level.

The project didn’t pass the first stage which finished on creating interactive screens (both arabic and english) and navigating between these screens using the rotary switch.

The project was built as a layer above the u8g library which was at the time a library that provide API’s  to control the GLCD directly without caring about the low level details of the communication protocol. The real challenge was to create api’s that draw arabic words. 

In the template.c file exits the api that draws an arabic string and many another api’s that helped in drawing the final screen like write a word in centered in the middle of box that suits that word in the size and make the box shallow or filled to distinguish between the options when using the rotary switch.
