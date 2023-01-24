# TVC
Estudo e Desenvolvimento Preliminar de Um Sistema de Empuxo Vetorial Para Foguetemodelismo

Os códigos que compõem a pesquisa são xxx. O code_v2 corresponde a tentativa de implementar o sistema de controle de empuxo vetorial, utilizando sistema de controle PID. Aqui, lê-se os valores do sensor MPU e aplica-se um sistema de controle PID para transformar os valores de entrada para valores de saída do servo motor. 
O código code_v3 deflete o servomotor entre valores limites e coleta o valor de angulação captado pelo sensor MPU. Esse código é utilizado para verificar-se a funcionalidade do MPU e também a deflexão do tubo articulado proporcionada pela vetorização do empuxo.
O código "mpu1" é a simples leitura dos valores fornecidos pelo sensor, e o "servo1" um simples comando oscilatório ao servomotor.

A biblioteca "Arduino-PID-Library-master" é necessária para fazer o sistema de controle PID funcionar corretamente.

Os códigos podem ser baixados e editados como quiser. Dentro da pasta também há a esquematização do circuito criado para controlar o sistema de empuxo vetorial e fotos do aparato de testes montado.
