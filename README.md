O problema do Papai Noel

Pela especificação do problema, o Papai Noel está dormindo e só deve ser acordado em dois casos:

1 - quando um número X de elfos precisa de sua ajuda;
2 - quando todas as suas Y renas chegaram de férias e ele deve partir entregar presentes.


Nossa animação para o problema acima está presente no arquivo santa.c. Ao executar o programa, pode-se observar na tela:

Na parte superior, o estado do Papai Noel. Se está dormindo, há "Z's" ao seu lado; quando acordado, seja ajudando elfos
ou amarrando as renas, aparece de olhos e boca abertos.

Ao lado direito, um indicador textual de quantos elfos há na fila esperando para ser ajudados pelo bom velhinho.
Abaixo de Noel, uma representação dos elfos sendo ajudados por ele. Quando o número de elfos chega a X,
Papai acorda e os ajuda; em seguida, esses elfos vão se retirando até o último sair; quando o faz,
os próximos da fila podem entrar.

Abaixo, uma representação do trenó e das renas que vão chegando de viagem. Quando esse número chega a Y,
Papai acorda, as amarra, e parte em viagem. A execução do programa então se encerra.


CONSTANTES
O número de elfos que Noel ajuda de cada vez pode ser alterado na constante MAX_SIMULTANEOUS_ELVES.
O número total de elfos no Pólo Norte fica em MAX_ELVES.
O número de renas necessárias para puxar o trenó pode ser alterado em MAX_RAINDEER.
