<h1 align = "center">Rotina de interrupção e debouncing utilizando botões A e B da placa BitDogLab com microcontrolador RP2040</h1>

<p align = "center">O projeto apresentado utiliza a placa BitDogLab e seus componentes juntamente com a linguagem C para desenvolver a interação entre os Botões A e B com os Leds WS2812.</p>

---
<h3>🎯 Objetivos</h3>
<p>O programa desenvolvido em Linguagem C para placa Pi Pico W tem como principais objetivos:</p>

- ☑️ Fazer o LED RGB piscar continuamente 5 vezes por segundo na cor vermelha (conectado à GPIO 13)
- ☑️ Apresentar números de 0 a 9 na matriz de LEDS 5x5 WS2812
- ☑️ Fazer com que o Botão A (conectado à GPIO 5) incremente os números na Matriz de LEDS 5x5 WS2818 (conectado à GPIO 7)
- ☑️ Fazer com que o Botão B (conectado à GPIO 6) decremente os números na Matriz de LEDS 5x5 WS2818 (conectado à GPIO 7)
- ☑️ Estabelecer rotina de interrupção para cada botão
- ☑️ Desenvolver o Debouncing para cada botão
  
---
<h3>🛠️ Ferramentas</h3>

  - Placa BitDogLab
  - Cabo tipo micro-usb para usb-a
  - Ferramentas CMake e Pico SDK instaladas
---

<h3>🚀 Utilizando o programa</h3>

Siga as etapas a seguir:
  - Pressione o botão "Bootsel" da placa
  - Conecte a placa no computador e solte o botão "Bootsel"
  - Clone o repositório usando o comando abaixo
    
    ```gitconfig
    git clone https://github.com/nevaskab/pio_button.git
    ```
  - Compile e Rode o código <br>

    ![Captura de tela 2025-01-19 150112](https://github.com/user-attachments/assets/62fbcc03-5653-4826-be75-316d8e6581bb)

  - Pronto! Sua placa, devidamente conectada, será capaz de rodar o código :D <br>

  - Aperte o botão A para incrementar os números exibidos na matriz 5x5 (Número atual + 1) <br>
  ![image](https://github.com/user-attachments/assets/ba9fce76-38ce-48d7-a005-48ff8b5971fd)

  - Aperte o Botão B para decrementar os números exibidos na matriz 5x5 (Número atual - 1) <br>
  ![image](https://github.com/user-attachments/assets/9797e98b-bee2-4067-87aa-a199651bb29d)

  - O LED RGB está configurado para piscar 5 vezes por segundo <br>
---

<h2>Para mais detalhe sobre o funcionamento...</h2>
Visite: https://drive.google.com/file/d/1y-QtxUZpLUwN4JEu_1G4mcBoxaMCvu6P/view?usp=sharing

### Autor
---
<a><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/133506658?s=400&u=add96d4ebb6071b0473386091845a1509b3de27b&v=4" width="100px;" alt=""/>
<br />
<sub><b>Andressa Martins</b></sub></a>

Feito por Andressa Martins. Entre em contato <3.

<a href="mailto:andressa.devsystem@gmail.com"><img alt="Static Badge" src="https://img.shields.io/badge/andressa.devsystem%40gmail.com-black?style=flat&logo=gmail&logoColor=%23EA4335&logoSize=auto&color=EDF2F4"></a>
