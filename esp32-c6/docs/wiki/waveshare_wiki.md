<html> 
<meta http-equiv="refresh" content="0; url=https://docs.waveshare.com/ESP32-C6-Touch-LCD-1.47">
</html>
<div class="wiki-pages jet-green-color">

{{Infobox item|colorscheme=green
|name = ESP32-C6-Touch-LCD-1.47
|img=[[File:ESP32-C6-Touch-LCD-1.47-details-3-2.jpg|alt=ESP32-C6-Touch-LCD-1.47|link=https://www.waveshare.com/esp32-c6-touch-lcd-1.47.htm | ESP32-C6-Touch-LCD-1.47]]
|caption=172×320, I2C / SPI
|{{#ifeq: {{#urlget:amazon|0}}|{{#urlget:Amazon|0}}| default|}}=display
|category1=ESP32-C6-Touch-LCD-1.47
|brand=Waveshare
|feature-name1= 显示尺寸
||feature-value1= 1.47 英寸
|feature-name2= 分辨率
|feature-value2= 172×320
|-
| interface1 = SPI
| interface2 = I2C
}}

<div class="toccolours mw-collapsible mw-collapsed">
=Overview=
<div class="mw-collapsible-content">

== Introduction ==
This product a microcontroller development board that adopts ESP32-C6FH8 and supports 2.4GHz Wi-Fi 6 and Bluetooth BLE 5. It integrates 8MB Flash and has onboard 1.47inch capacitive touch LCD screen, can smoothly run GUI programs such as LVGL. Combined with various peripheral interfaces, it is suitable for the quick development of the HMI and other ESP32-C6 applications.
== Features ==
*Equipped with a high-performance 32-bit RISC-V processor with clock speed up to 160 MHz, and a low-power 32-bit RISC-V processor with clock speed as low as 20MHz
*Supports 2.4 GHz Wi-Fi 6 (802.11 ax/b/g/n) and Bluetooth 5 (BLE) wireless communication protocols, with onboard antenna
*Built-in 320KB ROM, 512KB HP SRAM, 16KB LP SRAM, and 8MB Flash
*Onboard 1.47inch capacitive touch LCD display, 172×320 resolution, 262K color
*Brings out most GPIO pins, and supports USB full-speed standard
*Onboard TF card slot, supporting external TF card storage for pictures or files
*Supports accurate control such as flexible clock and multiple power modes to realize low power consumption in different scenarios
==Specifications==
{|border=1; style="width:800px;" align="auto"
|-
|style="background:#7eb128; color:black;text-align:center;"| Parameter name
|style="background:#7eb128; color:black;text-align:center;" | Parameter
|-
|style="text-align:center;"|Interface
|style="text-align:center;" |USB Type-C
|-
|style="text-align:center;"|Controller chip
|style="text-align:center;" |ESP32-C6
|-
|style="text-align:center;"|LCD type
|style="text-align:center;" |ISP
|-
|style="text-align:center;"|Screen resolution
|style="text-align:center;" |172 × 320
|-
|style="text-align:center;" rowspan="1"|Display chip
|style="text-align:center;" |JD9853
|-
|style="text-align:center;" rowspan="1"|Touch chip
|style="text-align:center;" |AXS5106L
|}

==Interfaces==
[[File:ESP32-C6-Touch-LCD-1.47-details-inter.jpg]]

== Dimensions ==
[[File:ESP32-C6-Touch-LCD-1.47-details-size.jpg]]

</div></div>

=Usage Instructions=
ESP32-C6-Touch-LCD-1.47 currently provides two development tools and frameworks, '''Arduino IDE''' and '''ESP-IDF''', providing flexible development options, you can choose the right development tool according to your project needs and personal habits.

==Development Tools==
{|
|-
!style="width: 180px;" |
!
|-
| [[File:270px-Arduino-IDE-logo.jpg|180px]] || 
===Arduino IDE===
Arduino IDE is an open source electronic prototyping platform, convenient and flexible, easy to get started. After a simple learning, you can start to develop quickly. At the same time, Arduino has a large global user community, providing an abundance of open source code, project examples and tutorials, as well as rich library resources, encapsulating complex functions, allowing developers to quickly implement various functions.
|-
<!--| [[File:MicroPython-logo.jpg|180px]] ||
===MicroPython===
Micropython is a full implementation of the Python 3 programming language that runs directly on embedded hardware such as ESP32, Raspberry Pi Pico, etc. You can run Python scripts directly on the board through REPL, which is very suitable for rapid prototyping. -->
|-
| [[File:270px-ESP-IDF-logo.jpg|180px]] || 
===ESP-IDF===
ESP-IDF, or full name Espressif IDE, is a professional development framework introduced by Espressif Technology for the ESP series chips. It is developed using the C language, including a compiler, debugger, and flashing tool, etc., and can be developed via the command lines or through an integrated development environment (such as Visual Studio Code with the Espressif IDF plugin). The plugin offers features such as code navigation, project management, and debugging, etc.
|}

Each of these two development approaches has its own advantages, and developers can choose according to their needs and skill levels. Arduino <!--and MicroPython -->are suitable for beginners and non-professionals because they are easy to learn and quick to get started. ESP-IDF is a better choice for developers with a professional background or high performance requirements, as it provides more advanced development tools and greater control capabilities for the development of complex projects.

==Components Preparation==
*ESP32-C6-Touch-LCD-1.47 x1
*TF card x 1 (32GB and below)
*Card reader x1

{{Note|Before operating, it is recommended to browse the table of contents to quickly understand the document structure. For smooth operation, please read the [[#FAQ|FAQ]] carefully to understand possible problems in advance. All resources in the document are provided with hyperlinks for easy download. |warn}}

=Working with Arduino=
This chapter introduces setting up the Arduino environment, including the Arduino IDE, management of ESP32 boards, installation of related libraries, program compilation and downloading, as well as testing demos. It aims to help users master the development board and facilitate secondary development.

==Environment Setup==
===Download and Install Arduino IDE ===
* Click to visit the [https://www.arduino.cc/en/software Arduino official website], select the corresponding system and system bit to download <br>[[File:ESP32-S3-AMOLED-1.91-Ar-software-01.png]]
* Run the installer and install all by default

===Install ESP32 Development Board ===
*Before using ESP32-related motherboards with the Arduino IDE, you must first install the software package for the '''esp32 by Espressif Systems''' development board
*According to <font color=red>''' board installation requirement'''</font>, it is generally recommended to use '''Install Online'''. If online installation fails, use '''Install Offline'''.
*For the installation tutorial, please refer to [https://www.waveshare.com/wiki/Arduino_Board_Managers_Tutorial Arduino board manager tutorial]
{| class="wikitable table table-bordered" style="width:80%"
|+ 
*ESP32-C6-Touch-LCD-1.47 required development board installation description
|-  
! Board name!! Board installation requirement!! Version number requirement 
|-style="text-align:center;"
| esp32 by Espressif Systems || "Install Offline" / "Install Online" || ≥3.0.0
|-
|}

===Install Library ===
*When installing Arduino libraries, there are usually two ways to choose from: '''Install online''' and '''Install offline'''.''' <font color=red> If the library installation requires offline installation, you must use the provided library file'''</font><br /> For most libraries, users can easily search and install them through the online library manager of the Arduino software. However, some open-source libraries or custom libraries are not synchronized to the Arduino Library Manager, so they cannot be acquired through online searches. In this case, users can only manually install these libraries offline.
*For library installation tutorial, please refer to [https://www.waveshare.com/wiki/Arduino_Library_Manager_Tutorial Arduino library manager tutorial]
* '''ESP32-C6-Touch-LCD-1.47 library file path: '''<pre>..\ESP32-C6-Touch-LCD-1.47-Demo\Arduino\libraries</pre>
{| class="wikitable table table-bordered" style="width:80%"
|+ 
*ESP32-C6-Touch-LCD-1.47 Library file installation instructions
|-
! Library Name  !!  Description  !!  Version  !!  Library Installation Requirement 
|-style="text-align:center;"
|| lvgl || Graphical library || v8.4.0 || "Install Online" (requires copying the demos folder to src)
|-
|-style="text-align:center;"
|| GFX_Library_for_Arduino || LCD driver library|| v1.5.9 || "Install Online"
|-
|-style="text-align:center;"
|| FastIMU || IUM driver library || v1.2.8 || "Install Online"
|-
|-style="text-align:center;"
|| esp_lcd_touch_axs5106l|| Touch driver library || -- ||  "Install Offline"
|-
|}
<!--
{{Note|For more learning and use of LVGL, please refer to *[https://docs.lvgl.io/master/intro/introduction/index.html LVGL official documentation]|info}}
-->
{{Run the first Arduino demo}}

==Demo==
{| class="wikitable table table-striped table-bordered" style="width:80%;background: white;"
|+ 
*ESP32-C6-Touch-LCD-1.47 Demo
|-
! Demo !! Basic Description !! Dependency Library
|-style="text-align:center;"
| 01_gfx_helloworld || HelloWorld is displayed on the screen|| GFX_Library_for_Arduino
|-style="text-align:center;"
| 02_qmi8658_output || Serial port prints QMI8658 data || FastIMU
|-style="text-align:center;"
| 03_sd_card_test || Test TF card || --
|-style="text-align:center;"
| 04_lvgl_arduino_v8|| lvgl demos || lvgl, GFX_Library_for_Arduino, esp_lcd_touch_axs5106l
|-style="text-align:center;"
| 05_lvgl_battery || Use the LVGL library to display the battery voltage || lvgl, GFX_Library_for_Arduino, esp_lcd_touch_axs5106l
|-style="text-align:center;"
| 06_lvgl_brightness || Use the LVGL library to control and display screen brightness || lvgl, GFX_Library_for_Arduino, esp_lcd_touch_axs5106l
|-style="text-align:center;"
| 07_lvgl_qmi8658 || Use the LVGL library to display QMI8658 data || lvgl, GFX_Library_for_Arduino, FastIMU, esp_lcd_touch_axs5106l
|-style="text-align:center;"
| 08_lvgl_image || Use the LVGL library to display images || lvgl, GFX_Library_for_Arduino, esp_lcd_touch_axs5106l
|}

===Arduino Project Parameter Setting===
*Each demo must be configured with parameters before flashing
[[File:ESP32-C6-Touch-LCD-1.47-Demo-01.png]]

===01_gfx_helloworld===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 uses the GFX_Library_for_Arduino library to drive the screen and display HelloWorld on the screen
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
*Create an object bus of the Arduino_ESP32SPI class to configure the SPI bus GPIO, and create an object gfx of the Arduino_ST7789 class to drive the ST7789 display
<pre>
Arduino_DataBus *bus = new Arduino_ESP32SPI(45 /* DC */, 21 /* CS */, 38 /* SCK */, 39 /* MOSI */);

Arduino_GFX *gfx = new Arduino_ST7789(
  bus, 47 /* RST */, 0 /* rotation */, false /* IPS */,
  172 /* width */, 320 /* height */,
  34 /*col_offset1*/, 0 /*uint8_t row_offset1*/,
  34 /*col_offset2*/, 0 /*row_offset2*/);
</pre>
|title4=Result demonstration
|content4=
*HelloWorld is displayed on the screen.
[[File:ESP32-C6-Touch-LCD-1.47-Demo-04.jpg|400px]]
}}

===02_qmi8658_output===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 acquires QMI8658 data and prints it using serial port
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
*Initialize QMI8658
<pre>
int err = IMU.init(calib, IMU_ADDRESS);
if (err != 0) {
  Serial.print("Error initializing IMU: ");
  Serial.println(err);
  while (true) {
    ;
  }
}
</pre>
|title4=Result demonstration
|content4=
*Open the serial port monitor to see the accel and gyro data of the X, Y, and Z axes printed
[[File:600px-ESP32-C6-Touch-LCD-1.47-Demo-02.png|400px]]
}}

===03_sd_card_test===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 tests the read and write functions of the TF card
|title2=Hardware connection
|content2=
*Connect the board to the computer
*Insert the TF card into the card slot<font color=red>''' (TF card needs to be formatted as FAT32)</font>
|title3=Code analysis
|content3=
*SPI interface initialization and TF card initialization
<pre>
#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs)) {
#else
  if (!SD.begin()) {
#endif
    Serial.println("Card Mount Failed");
    return;
  }
</pre>
|title4=Result demonstration
|content4=
*Insert the TF card into the computer, and you can find two more files: test.txt and foo.test. The content of the foo.txt is Hello World!, and the content of the test.txt is empty
[[File:ESP32-C6-Touch-LCD-1.47-Demo-05.png|300px]]

}}

=== 04_lvgl_arduino_v8 ===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 runs the lvgl demos
|title2=Hardware connection
|content2=
*Connect the board to the computer
'''<font color=red>|title3=Precautions
|content3=</font>'''
* If the lvgl library is installed online, you need to copy the demos folder to src
|title4=Code analysis
|content4=
* Select the lvgl demos to run
<pre>
lv_demo_widgets();
// lv_demo_benchmark();
// lv_demo_keypad_encoder();
// lv_demo_music();
// lv_demo_stress();
</pre>
|title5=Result demonstration
|content5=
* It can be operated by touch
[[File:ESP32-C6-Touch-LCD-1.47-Demo-06.jpg|400px]]
}}

===05_lvgl_battery===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 displays battery voltage and ADC values on the screen using the lvgl library
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
* Initialize the UI and create a 1000ms timer to obtain the data of the adc and convert the data into a voltage
<pre>
lvgl_battery_ui_init(lv_scr_act());
</pre>
|title4=Result demonstration
|content4=
[[File:ESP32-C6-Touch-LCD-1.47-Demo-07.jpg|400px]]
}}

===06_lvgl_brightness===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 displays the screen brightness on the screen using the lvgl library, and controls the screen brightness through the slider
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
* Initialize the UI, and create a slider value change callback, when the value of the slider changes, modify the screen brightness
<pre>
lvgl_brightness_ui_init(lv_scr_act());
</pre>
|title4=Result demonstration
|content4=
[[File:ESP32-C6-Touch-LCD-1.47-Demo-08.jpg|400px]]
}}

===07_lvgl_qmi8658===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 acquires QMI8658 data and displays it using the lvgl library
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
* Initialize the UI and create a 100ms timer to obtain data from QMI8658
<pre>
lvgl_qmi8658_ui_init(lv_scr_act());
</pre>

|title4=Result demonstration
|content4=
[[File:600px-ESP32-C6-Touch-LCD-1.47-Demo-03.jpg|400px]]
}}

===08_lvgl_image===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 runs the lvgl to display images.
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Preparation
|content3=
* Open [https://lvgl.io/tools/imageconverter lvgl Image Converter website]
* Import the image images/image_1.jpg and convert it, the image_1.c file will be generated
[[File:ESP32-C6-Touch-LCD-1.47-Demo-09.png|600px]]
* Copy image_1.c to the project folder
* Add the following code to 06_lvgl_image.ino to declare the image
<pre>
LV_IMG_DECLARE(image_1);
</pre>
* Set the image to be displayed
<pre>
lv_img_set_src(img, &image_1);
</pre>
|title4=Result demonstration
|content4=
[[File:ESP32-C6-Touch-LCD-1.47-Demo-11.jpg|400px]]
}}

=Working with ESP-IDF =
This chapter introduces setting up the ESP-IDF environment setup, including the installation of Visual Studio and the Espressif IDF plugin, program compilation, downloading, and testing of demos, to assist users in mastering the development board and facilitating secondary development.

==Environment Setup==
===Download and Install Visual Studio ===
* Open the download page of [https://code.visualstudio.com/download VScode official website], choose the corresponding system and system bit to download<br>[[File:ESP32-S3-AMOLED-1.91-VScode-01.png]]
* After running the installation package, the rest can be installed by default, but here for the subsequent experience, it is recommended to check boxes 1, 2, and 3<br> [[File:ESP32-S3-AMOLED-1.91-VScode-02.png]]
** After the first two items are enabled, you can open VSCode directly by right-clicking files or directories, which can improve the subsequent user experience
** After the third item is enabled, you can select VSCode directly when you choose how to open it
{{Note|The environment setup is carried out on the Windows 10 system, Linux and Mac users can access [https://docs.espressif.com/projects/esp-idf/en/v5.1.4/esp32s3/get-started/windows-setup.html ESP-IDF environment setup] for reference|info}}
<!--
{{Note|For more instructions on how to use the Arduino IDE, please refer to [https://docs.arduino.cc/software/ide/ Arduino Official Documentation]|info}}
-->

===Install Espressif IDF Plugin===
<!--*To use ESP32-related motherboards in Arduino IDE, you must first install the '''Arduino-ESP32 Board''' library -->
*It is generally recommended to use '''Install Online'''. If online installation fails due to network factor, use '''Install Offline'''
*For more information about how to install the Espressif IDF plugin, see [https://www.waveshare.com/wiki/Install_Espressif_IDF_Plugin_Tutorial Install Espressif IDF Plugin]
{{Run the first ESP-IDF demo}}

==Demo==
{| class="wikitable table table-striped table-bordered" style="width:80%;background: white;"
|+ 
*ESP32-C6-Touch-LCD-1.47 Demo
|-
! Demo !! Basic Description 
|-style="text-align:center;"
| 01_factory || Comprehensive test demo
|-style="text-align:center;"
| 02_sd_card_test || Test the read and write of the TF card
|-style="text-align:center;"
| 03_lvgl_example || Display lvgl demos
|-style="text-align:center;"
| 04_lvgl_image || Use lvgl library to display images

|}

=== 01_factory ===
{{Demo
|title1=Demo description
|content1=
This demo tests the functionality of the ESP32-C6-Touch-LCD-1.47 onboard modules, the information of each module will be displayed on the screen, and the user can swipe left and right through the touch screen to switch between pages
|title2=Hardware connection
|content2=
*Connect the board to the computer
* Insert the TF card into the card slot
|title3=Code analysis
|content3=
*Peripheral initialization
<pre>
    i2c_bus_handle = bsp_i2c_init();
    bsp_battery_init();
    bsp_wifi_init("WSTEST", "waveshare0755");
    bsp_display_init(&io_handle, &panel_handle, EXAMPLE_LCD_H_RES * EXAMPLE_LCD_DRAW_BUFF_HEIGHT);
    bsp_touch_init(&touch_handle, i2c_bus_handle, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, EXAMPLE_DISPLAY_ROTATION);
    bsp_sdcard_init();
    ESP_ERROR_CHECK(app_lvgl_init());
    lv_fs_fatfs_init();


    bsp_display_brightness_init();
    bsp_display_set_brightness(100);
</pre>

*LVGL graphics library configuration
<pre>
if (lvgl_port_lock(0))
{
    lvgl_ui_init();
    lvgl_port_unlock();
}
</pre>
|title4=Result demonstration
|content4=
[[File:300px-ESP32-C6-Touch-LCD-1.47-Demo-12.jpg|200px]]
[[File:300px-ESP32-C6-Touch-LCD-1.47-Demo-13.jpg|200px]]
[[File:300px-ESP32-C6-Touch-LCD-1.47-Demo-14.jpg|200px]]
[[File:300px-ESP32-C6-Touch-LCD-1.47-Demo-15.jpg|200px]]
[[File:300px-ESP32-C6-Touch-LCD-1.47-Demo-16.jpg|200px]]
}}

=== 02_sd_card_test ===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 tests the read and write functions of the TF card
|title2=Hardware connection
|content2=
*Connect the board to the computer
*Insert the TF card into the card slot<font color=red>''' (TF card needs to be formatted as FAT32)</font>
|title3=Code analysis
|content3=
* Initialize SPI
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return;
    }
* Mount the TF card
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;
    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
</pre>
|title4=Result demonstration
|content4=
* Insert the TF card into the computer, and you can find three more files: test.txt, FOO.TXT and NIHAO.TXT. Among them,  the content of the FOO.TXT is Hello SD!, the content of the NIHAO.TXT is Hello SD!, and the content of the test.txt is empty
[[File:ESP32-C6-Touch-LCD-1.47-Demo-10.png|300px]]
}}

<div>

=== 03_lvgl_example ===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 runs the lvgl demos
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Code analysis
|content3=
* Select the lvgl demos to run
<pre>
        // lv_demo_benchmark();
        // lv_demo_music();
        lv_demo_widgets();
        lvgl_port_unlock();
</pre>
|title4=Result demonstration
|content4=
* It can be operated by touch
[[File:ESP32-C6-Touch-LCD-1.47-Demo-06.jpg|400px]]
}}

=== 04_lvgl_image ===
{{Demo
|title1=Demo description
|content1=
This demo demonstrates that ESP32-C6-Touch-LCD-1.47 runs the lvgl to display images.
|title2=Hardware connection
|content2=
*Connect the board to the computer
|title3=Preparation
|content3=
* Open [https://lvgl.io/tools/imageconverter lvgl Image Converter website]
* Import the image images/image_1.jpg and convert it, the image_1.c file will be generated
[[File:ESP32-C6-Touch-LCD-1.47-Demo-09.png|600px]]
* Copy image_1.c to the main folder
* Add "image_1.c" to the CMakeLists.txt in the main folder
<pre>
idf_component_register(SRCS "main.c" "image_1.c"
                    INCLUDE_DIRS ".")
</pre>
* Add the following code to main.c to declare the image
<pre>
LV_IMG_DECLARE(image_1);
</pre>
* Set the image to be displayed
<pre>
lv_img_set_src(img, &image_1);
</pre>
|title4=Result demonstration
|content4=
[[File:ESP32-C6-Touch-LCD-1.47-Demo-11.jpg|400px]]
}}

=Flash Firmware Flashing and Erasing=
<hr>
<div class="mw-collapsible-content" style="padding: 10px; background-color: #f9f9f9; border-radius: 10px;">
    <div style="margin-bottom: 20px;">
*'''The current demo provides test firmware, which can be used to test whether the onboard device functions properly by directly flashing the test firmware'''
* '''bin file path: '''<pre>..\ESP32-C6-Touch-LCD-1.47-Demo\Firmware</pre>
{{Note|[https://www.waveshare.com/wiki/Flash_Firmware_Flashing_and_Erasing Flash firmware flashing and erasing ] for reference |info}}
</div>
</div>
</div>

=Resources=
==Schematic Diagram==
*[https://files.waveshare.com/wiki/ESP32-C6-Touch-LCD-1.47/ESP32-C6-Touch-LCD-1.47-Schematic.pdf ESP32-C6-Touch-LCD-1.47 Schematic diagram]

==Demo==
*[https://files.waveshare.com/wiki/ESP32-C6-Touch-LCD-1.47/ESP32-C6-Touch-LCD-1.47-Demo.zip ESP32-C6-Touch-LCD-1.47 Demo]

== Project Document ==
*[https://files.waveshare.com/wiki/ESP32-C6-Touch-LCD-1.47/ESP32-C6-Touch-LCD-1.47-2D3D.zip ESP32-C6-Touch-LCD-1.47 2D/3D file]

==Datasheets==
=== ESP32-C6 ===
*[https://files.waveshare.com/wiki/common/ESP32-C6_Technical_Reference_Manual.pdf ESP32-C6 Technical Reference Manual]
*[https://files.waveshare.com/wiki/common/ESP32-C6_Series_Datasheet.pdf ESP32-C6  Series Datasheet]

==Software Tools==
===Arduino===
*[https://www.arduino.cc/en/software/ Arduino IDE Official download link]
*[https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html ESP32-Arduino official documentation]
*[https://drive.google.com/drive/folders/1Pcs_A4FKWvdSHnz9lEBYqOpr-noTMbIv?usp=sharing Arduino-ESP32 offline component package]

=== VScode ===
*[https://code.visualstudio.com/download VScode official website]
=== Firmware Flashing Tool ===
*[https://dl.espressif.com/public/flash_download_tool.zip Flash_download_tool]
<!--*[https://files.waveshare.com/wiki/common/Sscom5.13.1.zip SSCOM debugging assistant]-->

== Other Resource Links==
*[https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html ESP32-Arduino official documentation]
*[https://docs.lvgl.io/master/intro/introduction/index.html LVGL official documentation]

==Project Resources==
This section features third - party project resources. We merely provide links and bear no responsibility for content updates or maintenance. Thank you for your understanding.<br>

'''Andrei Drăgulescu-Smart Animated Kids Clock (ESP32-C6 + LVGL)'''<br>
<youtube height=400px, width=400px>https://www.youtube.com/watch?v=FQkz1KrQX3I</youtube>
*Youtube : [https://www.youtube.com/watch?v=FQkz1KrQX3I https://www.youtube.com/watch?v=FQkz1KrQX3I]
*Instructables : [https://www.instructables.com/Smart-Animated-Kids-Clock-ESP32-C6-LVGL/ https://www.instructables.com/Smart-Animated-Kids-Clock-ESP32-C6-LVGL/]
*Github : [https://github.com/andreimagic/ESP32_C6_Touch_LCD_1_47_LVGL_Animated_Clock https://github.com/andreimagic/ESP32_C6_Touch_LCD_1_47_LVGL_Animated_Clock]

=FAQ=
{{FAQ| What should I do if the Arduino demo does not show up after downloading? |
*[https://www.waveshare.com/wiki/ESP32-C6-Touch-LCD-1.47#Arduino_Project_Parameter_Setting Set Arduino Project Parameters] .
|||}}
{{FAQ| After the module downloads the demo and re-downloads it, why sometimes it can't connect to the serial port or the flashing fails? |
*Long press the BOOT button, plug in the USB at the same time, then release the BOOT button, at this time the module can enter the download mode, which can solve most of the problems that can not be downloaded.
|||}}
{{FAQ| Why does the module keep resetting and flicker when viewed the recognition status from the device manager? |
*It may be due to Flash blank and the USB port is not stable, you can long-press the BOOT button, press RESET at the same time, and then release RESET, and then release the BOOT button, at this time the module can enter the download mode to flash the firmware (demo) to solve the situation.
|||}}
{{FAQ| How to deal with the first compilation of the program being extremely slow?|
*It's normal for the first compilation to be slow, just be patient</br>
|||}}
{{FAQ| How to handle the display "waiting for download..." on the serial port after successfully ESP-IDF flashing? |
*If there is a reset button on the development board, press the reset button; if there is no reset button, please power it on again</br>
|||}}
{{FAQ| What should I do if I can't find the AppData folder? |
*Some AppData folders are hidden by default and can be set to show.
*English system: Explorer->View->Check "Hidden items"
*Chinese system: File Explorer -> View -> Display -> Check "Hidden Items"</br>
|||}}
{{FAQ| How do I check the COM port I use? |
*Windows system:
①View through Device Manager: Press the Windows + R keys to open the "Run" dialog box; input devmgmt.msc and press Enter to open the Device Manager; expand the "Ports (COM and LPT)" section, where all COM ports and their current statuses will be listed. <br>
②Use the command prompt to view: Open the Command Prompt (CMD), enter the "mode" command, which will display status information for all COM ports. <br>
③Check hardware connections: If you have already connected external devices to the COM port, the device usually occupies a port number, which can be determined by checking the connected hardware.
*Linux system:
①Use the dmesg command to view: Open the terminal. <br>
①Use the ls command to view: Enter ls /dev/ttyS* or ls /dev/ttyUSB* to list all serial port devices. <br>
③Use the setserial command to view: Enter setserial -g /dev/ttyS* to view the configuration information of all serial port devices. </br>
|||}}
{{FAQ| Why does the program flashing fail when using a MAC device? |
*Install [https://files.waveshare.com/wiki/common/CH34XSER_MAC.7z MAC Driver] and flash again.
|||}}
{{FAQ| How to use SquareLine Studio to design interfaces?|
*Please refer to [https://www.waveshare.com/wiki/Waveshare_SquareLine_Studio SquareLine Studio tutorial]
|||}}

=Support=
<br />{{Servicebox1}}</div>

</div>