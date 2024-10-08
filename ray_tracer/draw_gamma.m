tab = [2,6,23,54,97];
x = linspace(0,1,5);


figure
plot(x, tab)
xlabel("Luma (kolor piksela)")
ylabel("Luminacja wyświetlacza [cd/m2]")

%Normalizacja pomiarów
y = rescale(tab, 0, 1);

%kolory = [0,0.25,0.5,0.75,1];
%cftool(kolory, y) -> gamma=2.1489
gamma = 2.1489;

figure
hold on
xlabel("Luma (kolor piksela)")
ylabel("Znormalizowana luminacja wyświetlacza")
plot(x, y)
plot(x, x.^gamma)
plot(x, x.^(1/gamma))
legend("wyniki pomiarów", "krzywa gamma wyświetlacza", "krzywa korekcji gamma", 'location','northwest')
hold off


