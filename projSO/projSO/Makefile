CC = gcc
CFLAGS = -Wall -g
LDFLAGS = `pkg-config --cflags --libs gtk+-3.0`  # Include GTK for the task manager GUI

# Object files for each module
CONVERTER_OBJS = converter_imagem.o
HISTORY_OBJS = historico_comando.o
TASK_OBJS = task_manager.o
MAIN_OBJS = main.o

# Final executable
EXECUTABLE = myapp

all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJS) $(CONVERTER_OBJS) $(HISTORY_OBJS) $(TASK_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Individual source files
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDFLAGS)

converter_imagem.o: converter_imagem.c
	$(CC) $(CFLAGS) -c converter_imagem.c $(LDFLAGS)

historico_comando.o: historico_comando.c
	$(CC) $(CFLAGS) -c historico_comando.c $(LDFLAGS)

task_manager.o: task_manager.c
	$(CC) $(CFLAGS) -c task_manager.c $(LDFLAGS)

clean:
	rm -f *.o $(EXECUTABLE)

.PHONY: all clean
