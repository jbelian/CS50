from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    set_a = set(a.split(sep='\n'))
    set_b = set(b.split(sep='\n'))
    return set_a & set_b

def sentences(a, b):
    """Return sentences in both a and b"""

    set_a = sent_tokenize(a)
    set_b = sent_tokenize(b)
    return set_a & set_b

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    set_a = extract(a, n)
    set_b = extract(b, n)
    return set_a & set_b

def extract(s, n):
    substrings = []
    for i in range(len(s)-n+1):
        substrings.append(s[i:i+n])
    return substrings