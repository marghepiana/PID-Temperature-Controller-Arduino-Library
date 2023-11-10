# PID-Temperature-Controller-Arduino-Library

This PID contorller I designed was utilized by the Boston University iGEM team 2023, that I was part of. https://2023.igem.wiki/bostonu-hw/index.html


Goal of PID controller:
Maintaining precise temperature control is essential for optimizing cell growth efficiency. To achieve this, a temperature-controlled chamber with an unique PID temperature controller has been designed. This chamber with its PID controller not only was tested to ensure the safe housing of cells but also offers adaptability to various microscopes, minimizing abrupt temperature fluctuations during cell observation under the microscope. The primary objective is to allow users to select and maintain a user-defined temperature, tailored to the specific cell type being cultured for the experiment.

During the development of the environmental control chamber, I encountered significant challenges in maintaining precise temperature control. Despite implementing a code to shut down the heater upon reaching the setpoint, the temperature consistently exceeded the desired levels. To address this issue, I developed an innovative Arduino Library for a PID (Proportional-Integral-Derivative) temperature controller utilizing relays.

The main idea behind this library is that the algorithm looks at the preset input using algebra, the past by computing an integral, and the future by computing a  derivative. The crucial aspect of this PID controller, particularly in this context, is the derivative component. By predicting the next future temperature, the system is able to understand if there is a possibility of overshooting before it actually happens and therefore it shuts the heater down beforehand. 

Additionally, this library incorporates a built-in clock system that monitors the system's on and off cycles. If it detects that the system has been active for an extended duration, it initiates an automatic shutdown. This feature further minimizes the risk of overheating and enhances the safety of the system.

How to use it:
To use this PID controller download all the files and add them as an arduino library. You can then implement your own arduino code or use the sample provided. 




