#include <vector>
#include <algorithm>

/*
    Restrições:
        Counting/Pigeonhole: Requerem intervalo conhecido de valores inteiros.
        Radix: Funciona melhor com números ou strings de comprimento fixo.
        Bucket: Assume distribuição uniforme (ex: números entre 0 e 1).
    Eficiência:
        Todos têm complexidade O(n) quando as suposições são atendidas.
        Não são adequados para dados genéricos sem estrutura específica.
*/


// Ordena inteiros em um intervalo conhecido, contando a frequência de cada elemento.
void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end());
    std::vector<int> count(max_val + 1, 0);
    std::vector<int> output(arr.size());

    // Conta a frequência de cada elemento
    for (int num : arr) count[num]++;

    // Acumula as contagens para determinar posições
    for (int i = 1; i <= max_val; i++)
        count[i] += count[i - 1];

    // Constrói o array de saída
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    arr = output;
}

#include <vector>
#include <algorithm>


// Ordena números inteiros processando dígitos individualmente (usando Counting Sort para cada dígito).
// Função auxiliar para Counting Sort em um dígito específico (exp = 1, 10, 100, ...)
void countingSortForRadix(std::vector<int>& arr, int exp) {
    std::vector<int> output(arr.size());
    std::vector<int> count(10, 0);

    // Conta a frequência de cada dígito
    for (int num : arr) 
        count[(num / exp) % 10]++;

    // Acumula as contagens
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Constrói o array de saída
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    arr = output;
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}

// Ordena números distribuídos uniformemente (ex: entre 0 e 1) dividindo-os em "baldes" e ordenando cada balde.
#include <vector>
#include <algorithm>

void bucketSort(std::vector<float>& arr) {
    if (arr.empty()) return;

    int n = arr.size();
    std::vector<std::vector<float>> buckets(n);

    // Distribui os elementos nos baldes
    for (float num : arr) {
        int bucket_idx = n * num;
        buckets[bucket_idx].push_back(num);
    }

    // Ordena cada balde (pode usar Insertion Sort para pequenos conjuntos)
    for (auto& bucket : buckets)
        std::sort(bucket.begin(), bucket.end());

    // Concatena os baldes
    int idx = 0;
    for (auto& bucket : buckets)
        for (float num : bucket)
            arr[idx++] = num;
}

// Ordena inteiros em um intervalo conhecido, colocando cada elemento diretamente em sua posição correta.
#include <vector>
#include <algorithm>

void pigeonholeSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int min_val = *std::min_element(arr.begin(), arr.end());
    int max_val = *std::max_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;

    std::vector<int> pigeonholes(range, 0);
    std::vector<int> output;

    // Conta a frequência
    for (int num : arr)
        pigeonholes[num - min_val]++;

    // Reconstrói o array ordenado
    for (int i = 0; i < range; i++)
        while (pigeonholes[i]-- > 0)
            output.push_back(i + min_val);

    arr = output;
}