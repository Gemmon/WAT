import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from wordcloud import WordCloud
import matplotlib.pyplot as plt

text1 = """ Brać się do roboty, wroga bić już czas
Widzę zamiast mężczyzn mnóstwo bab wśród was
Takiej bandy nikt nie zlęknie się
Zadrżyjcie więc na dźwięk tych słów
Mężczyzn z was (mężczyzn z was) wkrótce sam (wkrótce sam) zrobię znów!
Z wierzchu masz być skałą, ma się żar w niej tlić
Każdy bój zwyciężysz; zawsze tak ma być
Dziś, gdy widzę was, niedobrze mi
Lecz wytężcie wreszcie słuch
Mężczyzn z was (mężczyzn z was) wkrótce sam (wkrótce sam) zrobię znów!
Co chwila coś zatyka mnie!
Ja ostatnio czuję dreszcze!
Nieraz z wuefu wiałem, byłem głąb
Ten gość dał im nieźle w kość!
"""

text2 = """Civril, przysłaniając oczy dłonią, popatrzył na słońce wychodzące zza drzew. Na rynku zaczynało się ożywiać, turkotały wozy i wózki, pierwsi przekupnie już zapełniali stragany towarem. Stukał młotek, piał kogut, głośno wrzeszczały mewy.
- Piękny dzień się zapowiada – rzekł Piętnastka w zadumie. Civril popatrzył na niego koso, ale nic nie powiedział.
- Konie jak, Tavik? – spytał Nohorn naciągając rękawice.
- Gotowe, osiodłane. Civril, wciąż ich mało na tym rynku.
- Będzie więcej.
- Wypadałoby coś zjeść.
- Później.
- Akurat. Będziesz miał później czas. I ochotę.
- Patrzcie – rzekł nagle Piętnastka.
Wiedźmin nadchodził od strony głównej uliczki, wchodził między stragany, zmierzał prosto na nich.
- Aha – powiedział Civril. – Renfri miała rację. Daj mi kuszę, Nohorn.
Zgarbił się, napiął cięciwę, przydeptując stopą strzemiączko. Starannie ułożył bełt w rowku. Wiedźmin szedł. Civril uniósł kuszę.
- Ani kroku dalej, Wiedźminie!
Geralt zatrzymał się. Około czterdziestu kroków dzieliło go od grupy.
- Gdzie jest Renfri?"""

text3 = """W obliczeniach był błąd. Nie przeszli nad atmosferą, ale zderzyli się z nią. Statek wbijał się w powietrze z grzmotem, od którego puchły bębenki. Rozpłaszczeni na legowiskach czuli dobijanie amortyzatorów, przednie ekrany zaszły płomieniem i zgasły, 
poduszka rozżarzonych gazów, napierająca na dziób, zatopiła zewnętrzne obiektywy, hamowanie było niedostateczne i opóźnione. Sterownię napełnił swąd rozgrzanej gumy, pod prasą deceleracji ślepli i głuchli, to był koniec, ale nawet tego nie mógł żaden pomyśleć, 
nie starczyło wszystkich sił, aby unieść klatkę piersiową, wciągnąć oddech, robiły to za nich do ostatka pracujące tlenopulsatory, wtłaczały w nich powietrze jak w pękające balony. Nagle grzmot ucichł."""

# wczytanie listy niepotrzebnych słów
with open('stopwords.txt', 'r', encoding='utf-8') as file:
    stpWords = file.read().splitlines()
    print(stpWords)

# tokenizacja tekstu
tokens1 = word_tokenize(text1)
tokens2 = word_tokenize(text2)
tokens3 = word_tokenize(text3)
# usunięcie niepotrzebnych słów
filtered_tokens1 = [word for word in tokens1 if word.lower() not in stpWords and word.isalpha()]
filtered_tokens2 = [word for word in tokens2 if word.lower() not in stpWords and word.isalpha()]
filtered_tokens3 = [word for word in tokens3 if word.lower() not in stpWords and word.isalpha()]
# łączenie tekstu do tworzenia chmury
filtered_text1 = ' '.join(filtered_tokens1)
filtered_text2 = ' '.join(filtered_tokens2)
filtered_text3 = ' '.join(filtered_tokens3)
# generowanie chmury
wordcloud1 = WordCloud(font_path='arial',width=800, height=400, background_color='white').generate(filtered_text1)
plt.figure(figsize=(10, 5))
plt.imshow(wordcloud1, interpolation='bilinear')
plt.axis('off')
plt.show()
wordcloud2 = WordCloud(font_path='arial',width=800, height=400, background_color='white').generate(filtered_text2)
plt.figure(figsize=(10, 5))
plt.imshow(wordcloud2, interpolation='bilinear')
plt.axis('off')
plt.show()
wordcloud3 = WordCloud(font_path='arial',width=800, height=400, background_color='white').generate(filtered_text3)
plt.figure(figsize=(10, 5))
plt.imshow(wordcloud3, interpolation='bilinear')
plt.axis('off')
plt.show()