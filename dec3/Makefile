CC=g++
C_FLAGS=
BIN=solve
BIN_BONUS=$(BIN)2
LIBS=/usr/local/lib/boost_1_82_0

all:$(BIN)

$(BIN): $(BIN).cpp
	$(CC) $(C_FLAGS) -I $(LIBS) $< -o $@

bonus: $(BIN_BONUS)

$(BIN_BONUS): $(BIN_BONUS).cpp
	$(CC) $(C_FLAGS) -I $(LIBS) $< -o $@

clean:
	rm -rf $(BIN) $(BIN_BONUS)