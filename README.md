# RoboNito2w

## Descripción
RoboNito2w es un robot de dos ruedas que evita obstáculos utilizando un servo, un escáner de ultrasonidos y LEDs RGB. El robot se mueve hacia adelante mientras no haya obstáculos en su camino, y se detiene cada 3 segundos para escanear su entorno y decidir la dirección a tomar. Si detecta un obstáculo a menos de 10 cm, retrocede, escanea y gira hacia la dirección con más espacio. Además, cuenta con un sensor táctil que, al activarse, detiene el robot, escanea y avanza hacia adelante para luego girar a la izquierda.

## Componentes y Conexiones

### Componentes
- Servo motor
- Sensor de ultrasonidos (HC-SR04)
- LEDs RGB (rojo, verde, azul)
- Motores y controlador de motores (L298N)
- Sensor táctil
- Arduino

### Conexiones
- **Servo Motor**: Conectar al pin A1.
- **Sensor de Ultrasonidos**: 
  - Pin de eco: A2
  - Pin de trigger: A3
- **LEDs RGB**:
  - LED rojo: pin 10
  - LED verde: pin 12
  - LED azul: pin 13
- **Motores**:
  - ENA: pin 11
  - ENB: pin 3
  - IN1: pin 8
  - IN2: pin 7
  - IN3: pin 6
  - IN4: pin 5
- **Sensor Táctil**: Conectar al pin 4.

## Librerías Utilizadas
- [Servo](https://www.arduino.cc/en/Reference/Servo)
- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)

## Instalación de Librerías
Para instalar las librerías necesarias, puedes utilizar el gestor de librerías de Arduino:
1. Abre el IDE de Arduino.
2. Ve a **Sketch** > **Include Library** > **Manage Libraries**.
3. En la barra de búsqueda, escribe `Servo` y selecciona la librería `Servo` de la lista. Haz clic en **Install**.
4. Repite el proceso para la librería `NewPing`.

## Uso
1. Conecta todos los componentes según las instrucciones anteriores.
2. Carga el código `robonito2w.ino` en tu Arduino.
3. Enciende el Arduino y observa cómo el robot se mueve y evita obstáculos.
4. Activa el sensor táctil para probar la funcionalidad de parada y giro.

## Funcionamiento del Código
- El robot se mueve hacia adelante mientras no detecte obstáculos a una distancia menor a 20 cm.
- Cada 3 segundos, se detiene y escanea su entorno para decidir la dirección a tomar.
- Si un obstáculo está a menos de 10 cm, retrocede, escanea y gira hacia la dirección con más espacio.
- Al activar el sensor táctil, el robot se detiene, escanea y avanza hacia adelante, luego gira a la izquierda.

Disfruta construyendo y programando tu RoboNito2w!

