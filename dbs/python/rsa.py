def find_p_q(e, n, m, s):
    # Try dividing n by small prime numbers to find p and q
    for i in range(2, n):
        if n % i == 0:
            p = i
            q = n // i
            break

    # Calculate phi(n)
    phi_n = (p - 1) * (q - 1)

    # Calculate d (private key)
    d = pow(e, -1, phi_n)

    # Decrypt the ciphertext
    decrypted_message = pow(s, d, n)

    return p, q, decrypted_message

e = 5
n = 391
m = 234
s = 81

p, q, decrypted_message = find_p_q(e, n, m, s)
print(f"p: {p}, q: {q}, decrypted message: {decrypted_message}")