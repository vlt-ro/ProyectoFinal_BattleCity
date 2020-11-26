# BattleCity

## Contribuidores

Andrés Santiago Duque Escobar

Valentina Roquemen Echeverry

## Acerca del juego

Battle City es un videojuego de tanques producido y publicado por Namco como una adaptación del clásico arcade Tank Battalion.

El objetivo del juego es controlar un tanque sobre un escenario plagado de tanques enemigos, evitando que destruyan su base militar. 

# Controles

* ![Flechas para moverse](https://img2.freepng.es/20180422/pge/kisspng-computer-keyboard-arrow-keys-clip-art-5adca312ee3014.5868969515244091069756.jpg) 

* ![Space para disparar](https://userscontent2.emaze.com/images/116fcc9b-4071-4b73-9905-a74d7f865e36/cdcd0e7a-8986-4c3f-90cd-80308757aaa8.png)


## Requerimientos

Este juego usa la librería SDL 2.0. Para instalarla en puede seguir las siguientes instrucciones: 

* Ubuntu

``` apt-get install libsdl2-dev ``` 

``` apt-get install libsdl2-image-dev ```

``` apt-get install libsdl2-ttf-dev ```

* Arch

``` pamac install lua-sdl2```

``` pacman -S lua-sdl2``` 

``` pamac install sdl_image``` 

``` pacman -S sdl_image``` 

* Mac

``` brew install sdl2 sdl_ttf sdl2_image``` 

## Instalación

1. Clonar el repositorio.

``` git clone https://github.com/vlt-ro/ProyectoFinal_BattleCity```

2. Abrir la terminal en la carpeta donde se clonó el repositorio y corra los siguientes comandos:

``` cd build ```

``` make ```

``` cp BattleCity ../BattleCity ```

3. Para correr el juego ejecute **desde** la carpeta en la que se clonó el repositorio, si no lo corre desde ahí le va a sacar un error al cargar las texturas:

``` ./BattleCity```
