![Problema do Caixeiro Viajante](https://i.ibb.co/FB9kQnV/TSP.png)

Implementação do Problema do Caixeiro-Viajante (Travelling Salesperson Problem) utilizando a heurística da busca pelo vizinho mais próximo (Nearest Neighbour Search).

## Descrição do problema

O Problema do Caixeiro Viajante (PCV) ou Travelling Salesperson Problem (TSP) é um problema que tenta determinar a menor rota para percorrer uma série de cidades (visitando uma única vez cada uma delas) e, no fim do percurso, retornando à cidade de origem. Ele é um problema de otimização NP-difícil inspirado na necessidade dos vendedores em realizar entregas em diversos locais percorrendo o menor caminho possível, reduzindo o tempo necessário para a viagem e os possíveis custos com transporte e combustível.

## Heurística utilizada para a implementação
A heurística "Nearest Neighbour Search (NNS)" foi implementada para a resolução do problema. O NNS foi um dos primeiros algoritmos a serem utilizados para solucionar o problema do caixeiro-viajante. Nessa implementação em C++, o caixeiro começa em uma cidade inicial (definida pelo usuário em coordenadas) e repetidamente visita a cidade mais próxima da que ele está, até que todas tenham sido visitadas.

<img src="https://i.ibb.co/86DgXXK/teste.png" alt="Demonstração visual do método NNS" width="30%" height="30%">

O seguinte [vídeo](https://drive.google.com/file/d/1sOhWwb7xeDqj9GmE5KjLyvA0wXom7dG-/view?usp=sharing) serve como complemento para a compreensão do problema e explicação do código, assim como a [apresentação](https://drive.google.com/file/d/1e8lsV4VAXPhKJ0PpjkJAz7MHwk3VVM71/view?usp=sharing) utilizada para explicar o problema e contextualizar os espectadores.
