from cs50 import get_string

def count_letters(text):
    cnt = 0
    for i in range(len(text)):
        if text[i].isalnum():
            cnt += 1;
    return cnt

def count_words(text):
    cnt = 0
    for i in range(len(text)):
        if text[i].isspace():
            cnt += 1
    return cnt + 1

def count_sentences(text):
    cnt = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            cnt += 1
    return cnt

text = get_string("Text: ");

l = count_letters(text) * 100.0 / count_words(text)
s = count_sentences(text) * 100.0 / count_words(text)
grade = int(round(0.0588 * l - 0.296 * s - 15.8))

if grade < 1:
    print(f"Before Grade 1\n")
elif grade > 16:
    print(f"Grade 16+\n")
else:
    print(f"Grade {grade}\n")