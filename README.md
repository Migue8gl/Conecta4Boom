# Conecta4Boom
Implementation of the famous Connect4 game modified and with heuristic AI.

- This project consists of the design of search algorithms with adversaries in an environment of
play. In this case, the game is the well-known four in a row or connect four, but with a small
extra feature (bomb tokens).
These bomb tokens add a new action to the game, which is to make them explode. In doing so,
we will destroy all the existing squares in that row that belong to the adversary, in this way, all the
boxes positioned above these will fall by gravity to the position of the previous pieces
exploited.
We have an objective to achieve in this practice, which is to beat the three opponents (ninja 1,
ninja 2 and ninja 3) with our implementation of the algorithm and heuristics. The algorithm to
implement could be either MiniMax or AlphaBeta (achieving in the latter a depth of
higher search, and therefore better results).

- To run it, do make and then ./Conecta4Boom.
