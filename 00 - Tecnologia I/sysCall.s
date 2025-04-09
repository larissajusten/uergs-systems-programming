# Para montá-lo digite    as syscall.s -o syscall.o
# Para gerar o executável digite    ld -s syscall.o  -o syscall
# Para executar digite    syscall

# As chamadas de sistema Linux estao definidas no arquivo /usr/include/asm/unistd.h

.data                   # Seção de dados inicializados
     O_RDONLY  = 0
     STDOUT    = 1
     SYS_EXIT  = 1
     SYS_READ  = 3
     SYS_WRITE = 4
     SYS_OPEN  = 5
     SYS_FORK  = 2
     len       = 10
     file:   .string   "Teste.txt\0"  # Arquivo a ser lido
     msg:    .string   "Alo mundo!\0" # Mensagem a ser escrita em STDOUT
     .comm   buf, 512                 # buffer com 512 Bytes

.text                   # Seção de código 
      .global  _start

_start:
      # Alô mundo 
	mov   $len, %edx		# Tamanho da mensagem 
	mov	$msg, %ecx		# apontador para o buffer 
	mov	$STDOUT, %ebx  		# Arquivo de saída: STDOUT
	mov	$SYS_WRITE, %eax    	# Número da chamada de sistema (write)
	int	$0x80			# Chamada do kernel


      # int open (const char *pathname, int flags, mode_t mode)
      mov $0, %edx              # Direitos de acesso 
      mov $O_RDONLY , %ecx      # (0) Abertura do arquivo para leitura     
      mov $file, %ebx           # Nome do arquivo a ser aberto
      mov $SYS_OPEN, %eax       # Número da chamada de sistema (open)
      int $0x80                 # Chamada do kernel

      # int read(int fd, void *buf, size_t count)
      mov $40,   %edx           # Quantidade de bytes a serem lidos
      mov $buf,   %ecx          # apontador para o buffer
      mov %eax,  %ebx           # Descritor do arquivo a ser lido
      mov $SYS_READ, %eax       # Número da chamada de sistema (read)
      int $0x80                 # Chamada do kernel

      # int write(int fd, const void *buf, size_t count)
      mov $40, %edx              # Tamanho da mensagem
      mov $buf, %ecx             # apontador para o buffer 
      mov $STDOUT, %ebx          # Arquivo de saída: STDOUT
      mov $SYS_WRITE, %eax       # Número da chamada de sistema (write)
      int $0x80                  # Chamada do kernel
	
      # void _exit(int status)
      mov $0, %ebx             # Código do exit
      mov $SYS_EXIT, %eax      # Número da chamada de sistema (exit)
      int $0x80                # Chamada do kernel



