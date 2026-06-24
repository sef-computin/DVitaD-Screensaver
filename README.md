# DVitaD Screensaver
 DVD screensaver for PSVita/PSTV
 
<img width="800" height="394" alt="dvitad" src="https://github.com/user-attachments/assets/34a47545-fd68-4acd-8e99-266a42d28027" />

## Overview
This project uses vita2d library to draw DVD logo and coloring it.
It uses Doom RNG table for choosing color.

## Installation

1.  **Clone the Repository**:
    
    ```bash
    git clone https://github.com/sef-computin/DVitaD-Screensaver.git
    cd DVitaDScreensaver
    ```
    
2.  **Install Dependencies**:
    
    Make sure you have Make, vitaSDK and vita2d installed.
    Please refer to ![VitaSDK docs](https://github.com/vitasdk).

3.  **Build the Project**:

    When you have everything set up, just run:
    
    ```bash
    make all
    ```
    to build .vpk (you will then have to transfer it to your Vita)

    or if you have a running FTP server on Vita, you can run:
    
    ```bash
    make vpksend
    ```    
    to send it to Vita directly

 4. **Install VPK**
    
    You can install vpk through VitaShell or VPK manager of your preference.
