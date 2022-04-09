numeros = ('zero', 'um', 'dois', 'tres', 'quatro', 'cinco', 'seis', 'sete', 'oito', 'nove', 'dez', 'onze', 'doze',
           'treze', 'quatorze', 'quinze', 'dezesseis', 'dezessete', 'dezoito', 'dezenove', 'vinte')

print(numeros)

while True:
    var = int(input('Digite um numero entre 0 e 20: '))
    while var < 0:
        var = int(input('Digite um numero válido: '))

    while var > 20:
        var = int(input('Digite um numero válido: '))

    print(f"O numero digitado eh o {numeros[var]}")