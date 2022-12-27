# Codice

Invoca *una volta* il seguente comando shell per creare il file `build.ninja`
```bash
cmake -G Ninja .
```

Una volta creato `build.ninja`, usa il seguente comando ogni volta che vuoi compilare uno degli esempi.
```bash
ninja
```

### `06_smart_pointer`

Questo esempio produce volontariamente un *memory leak* per dimostrare l'efficacia degli *smart pointer*.
Per evidenziare come i puntatori tradizionali e gli smart pointer gestiscono la memoria allocata, utilizzare `valgrind` invocando il seguente comando sul terminale

```bash
valgrind ./06_smart_pointer
```
