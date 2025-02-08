# Restrições:
#     Bucket Sort: Assume números entre [0, 1) (ajuste o código se necessário).
#     Radix Sort: Funciona apenas para inteiros não negativos (modifique para tratar negativos se necessário).

# Eficiência:
#     Mantêm complexidade O(n) quando as suposições são atendidas.
#     São mais simples de implementar em Python devido à flexibilidade das listas.

#Ordena inteiros em um intervalo conhecido usando contagem de frequência.
def counting_sort(arr):
    if not arr:
        return
    
    max_val = max(arr)
    count = [0] * (max_val + 1)
    output = [0] * len(arr)
    
    # Conta a frequência de cada elemento
    for num in arr:
        count[num] += 1
    
    # Acumula as contagens para determinar posições
    for i in range(1, max_val + 1):
        count[i] += count[i - 1]
    
    # Constrói o array de saída (do fim para o início para garantir estabilidade)
    for i in range(len(arr) - 1, -1, -1):
        num = arr[i]
        output[count[num] - 1] = num
        count[num] -= 1
    
    # Atualiza o array original
    arr[:] = output

#Ordena números inteiros processando dígitos individualmente (usando Counting Sort para cada dígito).
def counting_sort_for_radix(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10  # Dígitos de 0 a 9
    
    # Conta a frequência de cada dígito
    for num in arr:
        index = (num // exp) % 10
        count[index] += 1
    
    # Acumula as contagens
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # Constrói o array de saída
    for i in range(n - 1, -1, -1):
        num = arr[i]
        index = (num // exp) % 10
        output[count[index] - 1] = num
        count[index] -= 1
    
    # Atualiza o array original
    arr[:] = output

def radix_sort(arr):
    if not arr:
        return
    
    max_val = max(arr)
    exp = 1  # Começa pelo dígito menos significativo
    
    while max_val // exp > 0:
        counting_sort_for_radix(arr, exp)
        exp *= 10  # Move para o próximo dígito

#Ordena números distribuídos uniformemente (ex: entre 0 e 1) usando "baldes".
def bucket_sort(arr):
    if not arr:
        return
    
    n = len(arr)
    buckets = [[] for _ in range(n)]
    
    # Distribui os elementos nos baldes
    for num in arr:
        bucket_idx = int(n * num)  # Assume números entre [0, 1)
        buckets[bucket_idx].append(num)
    
    # Ordena cada balde e concatena
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(sorted(bucket))  # Ordena com TimSort (híbrido)
    
    # Atualiza o array original
    arr[:] = sorted_arr

#Ordena inteiros em um intervalo conhecido usando "casas" diretas.
def pigeonhole_sort(arr):
    if not arr:
        return
    
    min_val = min(arr)
    max_val = max(arr)
    range_size = max_val - min_val + 1
    pigeonholes = [0] * range_size
    
    # Conta a frequência
    for num in arr:
        pigeonholes[num - min_val] += 1
    
    # Reconstrói o array ordenado
    sorted_arr = []
    for i in range(range_size):
        while pigeonholes[i] > 0:
            sorted_arr.append(i + min_val)
            pigeonholes[i] -= 1
    
    # Atualiza o array original
    arr[:] = sorted_arr

