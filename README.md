# BattleCity

## Contribuidores

Andrés Santiago Duque Escobar

Valentina Roquemen Echeverry

## Acerca del juego

Battle City es un videojuego de tanques producido y publicado por Namco como una adaptación del clásico arcade Tank Battalion.

El objetivo del juego es controlar un tanque sobre un escenario plagado de tanques enemigos, evitando que destruyan su base militar. 

# Controles

![flechas](resources/img/arrows.png) Flechas para moverse.

![space](resources/img/space.png) Barra espaciadora para disparar.

![enter](resources/img/enter.png) Enter para empezar el juego.

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
