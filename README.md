# 🐚 Minishell

<div align="center">

**Recreación de Bash desde cero en C**

[![42 School Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://www.42madrid.com/)
[![Made with C](https://img.shields.io/badge/Made%20with-C-A8B9CC?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))

> 💻 Un proyecto de 42 que implementa una shell UNIX funcional con parsing, pipelines y gestión de procesos.

---

[🔍 Shells](#-qué-es-un-shell) • [🛠️ Técnicas](#-técnicas-implementadas) • [📦 Instalación](#-instalación) • [⚙️ Funcionalidades](#️-funcionalidades) • [🏗️ Arquitectura](#-arquitectura-del-proyecto) • [👥 Autores](#-autores)
</div>

---

## 📖 Descripción del Proyecto

**Minishell** propone recrear las funcionalidades principales de **Bash**, implementando desde cero el parsing de comandos, la gestión de procesos con fork/exec, el manejo de pipelines y redirecciones, y la expansión de variables de entorno.

El proyecto incluye ejecución de comandos mediante PATH, built-ins nativos (`cd`, `echo`, `export`, etc.), redirecciones de I/O (`<`, `>`, `>>`, `<<`), pipelines con múltiples comandos, expansión de variables (`$VAR`, `$?`), y manejo correcto de señales UNIX.

---

## ✨ Características Principales

### Funcionalidades Básicas
- 📝 **Prompt interactivo** con historial de comandos
- 🔄 **Ejecución de comandos** del sistema mediante `PATH`
- 🧱 **Built-ins implementados**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- 🔀 **Pipelines**: Encadenamiento de comandos con `|`
- 📂 **Redirecciones**: `<`, `>`, `>>`, `<<` (heredoc)
- 💬 **Expansión de variables**: `$VAR`, `$?`
- 🎭 **Manejo de comillas**: Simples (`'`) y dobles (`"`)
- ⚡ **Señales**: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- 🎯 **Gestión de exit status** global

### Mejoras de Implementación
- 🔍 **Parser robusto** con validación de sintaxis
- 🧠 **Gestión de memoria** sin leaks
- 🚀 **Manejo de procesos** con fork/exec/wait
- 📊 **Exit codes precisos** compatibles con Bash
- 🔐 **Validación de argumentos** en built-ins

---

## 🔍 ¿Qué es una Shell?

Una **shell** es un intérprete de comandos que actúa como interfaz entre el usuario y el sistema operativo. A diferencia de las interfaces gráficas, la shell permite:

### Principio Básico
1. **Lectura**: Obtiene input del usuario (comando)
2. **Parsing**: Analiza y tokeniza el comando
3. **Expansión**: Expande variables de entorno
4. **Ejecución**: Lanza procesos mediante system calls
5. **Salida**: Muestra resultados al usuario

### Componentes Clave
- **Lexer/Parser**: Divide input en tokens y valida sintaxis
- **Expander**: Resuelve variables, etc.
- **Executor**: Gestiona procesos hijos y redirecciones
- **Signal Handler**: Responde a señales del sistema

---

## 🛠️ Técnicas Implementadas

### Parsing y Análisis Léxico
- **Tokenización**: División del input en tokens respetando comillas
- **Validación de sintaxis**: Detección de errores (`||`, `&&`, pipes mal formados)
- **Manejo de comillas**: Las simples bloquean expansión, las dobles la permiten
- **Split personalizado**: Algoritmo que respeta contexto de comillas

### Expansión de Variables
- **Variables de entorno**: `$VAR` expande a su valor
- **Exit status**: `$?` devuelve código de salida del último comando
- **Protección de comillas simples**: No expande dentro de `'...'`
- **Edge cases**: Manejo de `$`, `$$`, variables inexistentes

### Gestión de Procesos
- **Fork/Exec**: Creación de procesos hijos para comandos externos
- **Wait y exit status**: Captura de código de salida de procesos
- **Pipes**: Comunicación entre procesos mediante file descriptors
- **Built-ins directos**: Ejecución sin fork para modificar shell padre

### Redirecciones
- **Input**: `<` redirige entrada desde archivo
- **Output**: `>` sobrescribe, `>>` añade al final
- **Heredoc**: `<<` lee hasta delimitador expandiendo variables
- **File descriptors**: Uso de `dup2` para redirección de streams

### Manejo de Señales
- **SIGINT (Ctrl+C)**: Nueva línea en prompt, termina comando en ejecución
- **SIGQUIT (Ctrl+\\)**: Ignorado en prompt, termina con core dump en ejecución
- **EOF (Ctrl+D)**: Sale de la shell limpiamente
- **Configuración dinámica**: Diferentes handlers según contexto

### Estructura de Datos
- **Lista enlazada de comandos**: Para pipelines múltiples (`cmd1 | cmd2 | cmd3`)
- **Array dinámico de argumentos**: Gestión de comandos con N argumentos
- **Environment copy**: Copia profunda del entorno para modificaciones locales
- **Heredoc delimiters**: Array dinámico para múltiples heredocs

---

## 📦 Instalación

### Compilación
```bash
# Clonar el repositorio
git clone https://github.com/ccheerry/minishell.git
cd minishell

# Compilar el proyecto
make

# El ejecutable 'minishell' se generará en el directorio raíz
```

---


## ⚙️ Funcionalidades

### Built-ins Implementados

| Comando | Descripción | Opciones |
|---------|-------------|----------|
| `echo` | Imprime argumentos en stdout | `-n` (sin salto de línea) |
| `cd` | Cambia directorio actual | Ruta relativa o absoluta |
| `pwd` | Muestra directorio actual | - |
| `export` | Define/muestra variables de entorno | `VAR=value` o sin args |
| `unset` | Elimina variable de entorno | `VAR` |
| `env` | Muestra variables de entorno | - |
| `exit` | Sale de la shell | Código numérico opcional |

### Operadores y Redirecciones

| Operador | Función | Ejemplo |
|----------|---------|---------|
| `\|` | Pipeline entre comandos | `ls \| grep txt` |
| `<` | Redirección de entrada | `cat < file.txt` |
| `>` | Redirección de salida (sobrescribe) | `echo "test" > out.txt` |
| `>>` | Redirección de salida (append) | `echo "test" >> out.txt` |
| `<<` | Heredoc | `cat << EOF` |

### Expansión

| Sintaxis | Descripción | Ejemplo |
|----------|-------------|---------|
| `$VAR` | Expande variable | `echo $HOME` |
| `$?` | Exit status último comando | `echo $?` |
| `'...'` | Sin expansión | `echo '$HOME'` → `$HOME` |
| `"..."` | Con expansión | `echo "$HOME"` → `/home/user` |

---

## 🏗️ Arquitectura del Proyecto

```
minishell/
├── include/
│   ├── minishell.h          # Definiciones principales y estructuras
│   └── libft.h              # Prototipos de libft
├── src/
│   ├── minishell.c          # Loop principal y configuración
│   ├── parsing/             # Parser, lexer y validación
│   │   ├── parsing.c        # Punto de entrada del parsing
│   │   ├── parsing_pipes.c  # División por pipes
│   │   ├── parsing_args.c   # Separación de argumentos
│   │   ├── parsing_cmd.c    # Creación de estructuras t_cmd
│   │   ├── parsing_redirects.c      # Procesamiento de redirecciones
│   │   ├── parsing_redirects_stx.c  # Validación sintaxis redirecciones
│   │   └── parsing_syntax.c         # Validación general
│   ├── execution/           # Motor de ejecución
│   │   ├── execute_cmd.c            # Ejecución de comandos individuales
│   │   ├── execute_builtins_cmd.c   # Manejo de built-ins
│   │   ├── execute_pipes.c          # Gestión de pipelines
│   │   ├── execute_utils.c          # Helpers de redirecciones
│   │   └── execute_utils2.c         # Más utilities
│   ├── redirects/           # Sistema de redirecciones
│   │   ├── redirects.c              # Lógica principal
│   │   ├── redirects_parser.c       # Parsing de redirecciones
│   │   ├── redirects_handlers.c     # Handlers específicos
│   │   └── redirects_extract.c      # Extracción de filenames
│   ├── builtins/            # Implementación de built-ins
│   │   ├── builtins.c       # echo, pwd, env, unset
│   │   ├── builtin_cd.c     # Comando cd
│   │   ├── builtin_utils.c  # Utilidades compartidas
│   │   ├── builtins_exit.c  # Comando exit
│   │   ├── builtins_export.c        # Comando export
│   │   ├── builtins_utils.c         # Helpers para exit
│   │   ├── cd_utils.c               # Helpers para cd
│   │   └── export_utils.c           # Helpers para export
│   ├── environment.c        # Gestión de variables de entorno
│   ├── elim_env.c          # Eliminación de variables
│   ├── expand_vars.c       # Expansión de variables
│   ├── expand_utils.c      # Utilidades de expansión
│   ├── signals.c           # Manejo de señales
│   ├── memory.c            # Liberación de memoria
│   ├── utils.c             # Funciones auxiliares
│   └── utils2.c            # Más utilidades
├── libft/                   # Librería de funciones personalizadas
│   ├── ft_*.c              # Funciones de manipulación de strings, memoria, etc.
│   ├── libft.h             # Prototipos
│   └── Makefile
└── Makefile                 # Sistema de compilación
```

### Estructuras Principales

```c
typedef struct s_cmd
{
    char            **args;                 // Array de argumentos
    char            *infile;                // Archivo de entrada
    char            *outfile;               // Archivo de salida
    int             append;                 // Flag para >>
    int             heredoc;                // Flag para heredoc
    char            *delimiter;             // Delimitador de heredoc
    char            **heredoc_delimiters;   // Array de delimitadores
    int             heredoc_count;          // Contador de heredocs
    struct s_cmd    *next;                  // Siguiente comando (pipeline)
}   t_cmd;

typedef struct s_shell
{
    char    **envp;     // Copia del environment
    t_cmd   *cmds;      // Lista de comandos
}   t_shell;
```

---

## 🔧 Detalles Técnicos

### Algoritmo de Parsing

1. **Validación de sintaxis**: Pipes, redirecciones, comillas cerradas
2. **División por pipes**: Separación de comandos en cadena
3. **Extracción de redirecciones**: Identificación de `<`, `>`, `>>`, `<<`
4. **Parsing de argumentos**: Split respetando comillas
5. **Creación de estructuras**: Construcción de lista enlazada de `t_cmd`

### Pipeline de Ejecución

1. **Preprocesamiento**: Expansión de variables y eliminación de comillas
2. **Detección de tipo**: Built-in vs comando externo
3. **Configuración de redirecciones**: Setup de file descriptors
4. **Fork/Exec**: Creación de procesos (si no es built-in)
5. **Wait**: Captura de exit status
6. **Limpieza**: Cierre de FDs y liberación de memoria

### Gestión de Heredocs

Los heredocs se procesan secuencialmente:
- Se leen todas las líneas hasta encontrar el delimitador
- Se expanden variables en cada línea (excepto si delimitador tiene comillas)
- Se escriben en un pipe temporal
- El último heredoc es el que se usa como stdin

### Manejo de Pipes Múltiples

Para `cmd1 | cmd2 | cmd3`:
1. Se crea pipe entre cmd1 y cmd2
2. Fork de cmd1, redirección de stdout al pipe
3. Fork de cmd2, redirección recursiva (vuelve a ejecutar pipeline con cmd2 | cmd3)
4. Wait secuencial de todos los procesos

---

## 📚 Recursos y Referencias

### Documentación
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [GNU Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

### Temas Clave
- **Procesos UNIX**: fork, exec, wait, pipes
- **File Descriptors**: dup2, open, close
- **Señales**: signal, sigaction
- **Parsing**: Lexer, Parser, AST
- **Variables de entorno**: getenv, setenv, unsetenv

---

## 👥 Autores

Desarrollado como proyecto de **42 Madrid**

- [@ccheerry](https://github.com/ccheerry)
- [@AbelFerrer7](https://github.com/AbelFerrer7)

---

