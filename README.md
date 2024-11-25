<div align="center">

# 💡 MonitorLight 💡

IoT monitor light bar. Dimmable via websocket or USB.

</div>

![あああああ](https://github.com/user-attachments/assets/a6d9a29a-fd81-46ff-a85a-2eee5cd1c9b3)

## Feature

<details>
<summary> <code>./cad</code> 3D data (STL) of 3D printer parts </summary>

- Developed with Autodesk Fusion 360

</details>

<details>
<summary> <code>./firmware</code> Firmware running on M5StampC3U, responsible for driving neopixel LEDs and communication server. </summary>

- Developed with Arduino IDE

- Board URL : <https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json>

</details>

<details>
<summary> <code>./native-controller</code> Resident dimming application for windows made by WPF (C#). </summary>

- Developed with Visual Studio

  ![image](https://github.com/user-attachments/assets/f6d99cbc-5925-4aea-83dc-fb5290400b21)

</details>

<details>
<summary> <code>./web-controller</code> Dimming application via browser. </summary>

```sh
# NodeJS required
git clone https://github.com/CaseyNelson314/MonitorLight.git
cd ./MonitorLight/web-controller/src/
npm install
npm run dev
```

![image](https://github.com/user-attachments/assets/11dbccd9-787b-4c1a-9d81-6ced88464ddc)

</details>

## Communication path via websocket

<img width="70%" src="https://github.com/user-attachments/assets/4c2129d0-c696-419c-b10f-a3e419198722">

## Communication path via USB (Debug)

<img width="70%" src="https://github.com/user-attachments/assets/daa5c7fc-ea9a-4688-82ab-6567b5a32137">

## Lisence

MIT Lisence
