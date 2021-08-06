/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize(void);

/*********************************************************************
* Function: void APP_DeviceCustomHIDStart(void);
*
* Overview: Starts running the Custom HID demo.
*
* PreCondition: The device should be configured into the configuration
*   that contains the custome HID interface.  The APP_DeviceCustomHIDInitialize()
*   function should also have been called before calling this function.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDStart(void);

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks(void);

/** DEFINITIONS OF COMMANDS ****************************************/
enum
{
    COMMAND_TOGGLE_LED = 0x80,
    COMMAND_GET_BUTTON_STATUS_S2 = 0x81,
    COMMAND_GET_BUTTON_STATUS_S3 =0X82, //creado por mi para manejar S3  
    COMMAND_TOGGLE_LED_D4 = 0x83,  //creado por mi para manejar Led D4 
    COMMAND_CONTROL_MODE_SELECT=0x84, //creado por mi para seleccionar el modo del paso=0x84, 
    COMMAND_STOP_MOVIMIENTO_CONTINUO=0x85, 
    COMMAND_MOVIMIENTO_CONTINUO=0x86,//creado por mi para mover el step motor 
    COMMAND_READ_POTENTIOMETER = 0x37,
    COMMAND_READ_ERROR_STATUS =0X38 //creado por mi para mostrar error
            
} CUSTOM_HID_DEMO_COMMANDS;
