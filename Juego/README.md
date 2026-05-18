# Flash or Die — Parcial Final

## Integrantes
- Tomás Espinel Cohen
- Alejandro Mendez Santana

---

## Innovaciones Implementadas

### 1. Cinemáticas animadas en ASCII
Secuencia de imágenes ASCII que se alternan a 800ms para simular animación, con música sincronizada y opción de saltar con `e`.

### 2. Audio multiplataforma
Sistema de reproducción de sonido que detecta el sistema operativo en tiempo de compilación y usa la API correspondiente: `PlaySound` en Windows, `afplay` en Mac y `aplay` en Linux.

### 3. Sistema de eventos aleatorios
Al tocar una casilla `?`, se genera un evento con probabilidades definidas: 45% aparece un objeto, 30% aparece una interacción en el mapa, 25% aparece un enemigo.

### 4. Sistema de puzzle con objetos e interacciones
Cadena de crafteo que requiere explorar el mapa para conseguir materiales:
- `Moneda` → usar en `Well` → `MoldeParaLlave`
- `Cruz` → usar en `Seal` → `MercurioLiquido`
- `MoldeParaLlave` + `MercurioLiquido` → combinar → `MoldeConLiquido`
- `MoldeConLiquido` → usar en `Cooler` → `Llave`
- `Escopeta` + `Municion` → combinar → `EscopetaCargada`

### 5. Inventario con combinación de objetos
Sistema accesible con `i` que permite ver los objetos recogidos y combinar dos de ellos para obtener uno nuevo. La combinación consume ambos objetos del inventario.

### 6. Puerta con múltiples objetos y código numérico
La puerta final requiere insertar 3 objetos específicos en cualquier orden, y una vez insertados todos, pide un código de 7 dígitos para abrirse.

### 7. Sistema de combate con minijuegos — Fantasmas
Al encontrar un fantasma, el jugador elige entre 4 opciones, cada una con su propia mecánica:
- **Pelear:** sistema de flashes con imágenes alternadas entre estados de ataque y defensa.
- **Correr:** minijuego de reflejos donde el jugador debe presionar el número correcto dentro de una ventana de tiempo.
- **Pedir misericordia:** opción de rendición con consecuencias.

### 8. Boss con 3 fases y minijuegos
Jefe final con tres fases de combate distintas, el jugador debe sobrevivir por 7 minutos para ganar:
- **Fase 1:** el jugador debe moverse o detenerse según si la música está sonando.
- **Fase 2:** el jefe muestra palabras con caracteres especiales que el jugador debe escribir exactamente dentro de un tiempo límite.
- **Fase 3:** minijuego de ritmo donde el jugador debe presionar `L` al ritmo del latido del corazón en pantalla.

### 9. Imágenes 3D de objetos y enemigos
Al encontrar un objeto o enemigo, se abre automáticamente la imagen correspondiente usando el visor del sistema operativo (`start`, `open` o `xdg-open` según la plataforma).

### 10. Dos finales distintos
El juego tiene un final bueno y un final malo según el resultado del combate contra el jefe, ambos con cinematicas

### 11. Indicador visual de vida del jugador
La cara ASCII del jugador cambia visualmente según su nivel de vida: saludable (≥70), dañado (40–69) o crítico (<40).

---

## Uso verificable de punteros

El proyecto usa punteros en múltiples puntos de la lógica:

- **`eliminarDeInventario(const char* objeto)`** — recibe un puntero a cadena de caracteres
  en vez de un objeto por valor, evitando copias innecesarias.

- **`static const char* nombres[]`, `static const char* imagenes[]`** — arreglos de punteros
  a strings literales en `generarEvento()`, cumpliendo la restricción de memoria estática.

- **`const char* imagen = lista[rand() % 6]`** — puntero que apunta directamente
  a uno de los elementos del arreglo estático en `Monstruo()`.

- **`std::string* p = arr`** en `Cinematicas()` — puntero que recorre el arreglo
  de rutas de cinemáticas mediante aritmética de punteros (`*(p + i)`, `*(p + i + 1)`).

- **Referencias `int&`** en todas las funciones de gameplay (`movimiento`, `Fight`,
  `Correr`, `Flee`, `Monstruo`, `interactuarCon*`, etc.) — permiten modificar
  directamente `habitacion`, `fila` y `columna` del game-loop sin copiar los valores.

---

## Uso de Inteligencia Artificial

El proyecto fue desarrollado siguiendo las restricciones del parcial. A continuación se detalla el rol de la IA en cada parte del código:

### Arquitectura y movimiento
Para el sistema de movimiento y cambio de habitaciones, se consultó a la IA sobre qué estructura de datos usar. La IA sugirió usar un arreglo de structs (`Conexion`) para representar las conexiones entre habitaciones. La implementación completa del código fue realizada por el equipo.

### `cargarMapa`, `guardarMapa`, `mostrarMapa`
Mismo caso que el anterior: la IA orientó sobre el enfoque a tomar (leer carácter a carácter con `file.get()`), el código fue escrito por el equipo.

### `ResetearCuartos`
Se consultó a la IA sobre cómo copiar archivos en C++ para restaurar el estado original de los cuartos. La IA explicó el uso de `std::ifstream` y `std::ofstream` para copiar. El código fue implementado por el equipo.

### `Monstruo` — trigger de combate
La lógica del trigger fue creada sin asistencia de IA. Posteriormente se consultó a la IA sobre el uso de `_getch()` para capturar input sin esperar Enter, y se aplicó ese conocimiento al resto del proyecto.

### `Fight` — mecánica de pelea
Se solicitó orientación a la IA para implementar el sistema de flashes con imágenes alternas entre estados. Este sistema constituye una de las innovaciones del proyecto.

### `Correr`
Se consultó a la IA sobre el uso de `_getch()` para el minijuego de reflejos. El diseño completo del sistema fue realizado por el equipo.

### `Flee`
Se consultó a la IA sobre cómo seleccionar y cargar una habitación aleatoria al huir. El resto de la función fue implementado por el equipo.

### `Rendirse`, `Suerte`, `VidaJugador`, `Morir`
Implementados sin asistencia de IA.

### VerificarObjetoEnInventario
Tratamos de resolverlo con ciclos for pero no pudimos, aqui nos ayudo la IA.

### Sistema de inventario base (agregar y usar un objeto)
Desarrollado por Alejandro Mendez Santana. La IA orientó el enfoque general del sistema, pero el código fue escrito por él.

### Innovaciones de Alejandro (eventos, interacciones, puzzle de objetos, combinación)
Desarrolladas por Alejandro Mendez Santana. En la mayoría de los casos la IA actuó como guía de orientación. En los casos donde había errores de compilación que no podían resolverse, se consultó a la IA para corregir la estructura, pero la lógica y el diseño fueron decisión del desarrollador.

### Resto de innovaciones (sonido, imágenes, boss, cinemáticas)
Desarrolladas por Tomás Espinel Cohen. Las innovaciones que pudieron implementarse sin ayuda se hicieron sin IA. Cuando surgían errores de compilación, se consultaba a la IA para corregir la estructura. Cuando el conocimiento técnico necesario estaba fuera del alcance del curso (como APIs de audio por plataforma), se solicitó orientación específica a la IA.

### Resolver Warnings
Me salian Warnings referentes a #pragma comment, fila y columna sin usar en PonerPausa() y libreria winmm faltante. Le pedimos a la IA que significaba cada Warning y la raiz del problema para solucionarla nosotros.

## Posdata
Se que el repositorio se llama Calabozos y Punteros pero le decidimos cambiar el nombre a Flash or Die despues.

