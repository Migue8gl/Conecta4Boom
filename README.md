# Conecta4Boom
Implementación del famoso juego Conecta4 modificado y con IA heurística.

- Este proyecto consiste en el diseño de algoritmos de búsqueda con adversarios en un entorno de
juego. En este caso, el juego es el conocido cuatro en raya o conecta cuatro, pero con una pequeña
característica extra (fichas bomba).
Estas fichas bomba añaden al juego una nueva acción, que es la de hacerlas explotar. Al hacerlo,
destruiremos todas las casillas existentes en esa fila que sean del adversario, de este modo, todas las
casillas posicionadas arriba de estas caerán por gravedad a la posición de las fichas anteriormente
explotadas.
Tenemos un objetivo a realizar en esta práctica, que es el de vencer a los tres oponentes (ninja 1,
ninja 2 y ninja 3) con nuestra implementación del algoritmo y la heurística. El algoritmo a
implementar podía ser o MiniMax o AlphaBeta (consiguiendo en este último una profundidad de
búsqueda mayor, y por tanto, mejores resultados).
