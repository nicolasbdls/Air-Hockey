%Matlab file used in the final step of the project

X1=[77,76,75,76,66,71,75,104,177,239,297,343,390,422,452,484,508,531,551,570,548,520,487,458,419,384,360,335,314,292,269,249,227,210,199,182,172,162,144,120,101,72,54,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
]; Y1=[282,283,284,280,285,283,276,228,133,42,118,201,282,234,163,77,46,103,164,225,287,250,199,161,112,61,32,75,112,153,193,238,280,280,246,211,177,138,126,127,129,131,132,136,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
]; X2=[137,137,136,134,134,135,134,133,134,136,134,135,130,130,129,108,87,77,75,72,103,193,293,370,447,528,564,498,438,380,317,250,186,124,77,62,97,143,186,255,303,371,417,481,528,566,530,475,436,391,350,307,267,210,171,133,94,56,44,87,118,150,183,214,257,289,321,353,385,415,453,483,515,541,566,556,525,502,479,454,431,405,376,353,329,305,284,260,230,207,189,165,144,124,102,82,62,44,32
]; Y2=[282,281,283,282,281,281,282,285,281,284,280,280,278,280,278,280,285,283,282,281,239,183,88,36,105,179,234,280,274,240,206,169,132,100,70,38,61,94,106,104,101,97,96,93,92,90,105,123,137,153,166,180,194,213,228,240,253,266,272,269,268,265,263,264,259,257,255,253,251,251,249,248,245,243,241,238,235,234,230,229,226,224,221,217,213,211,208,205,201,199,195,193,190,188,185,182,179,177,176
];
Seq='Seq1m'
C2=[0.000000 1.000000 0.086275]
C3=[0.980392 0.164706 1.000000]
pause=10

clear pause

X1(find(X1<0))=NaN;
X2(find(X2<0))=NaN;

Y1(find(Y1<0))=NaN;
Y2(find(Y2<0))=NaN;

maxX=[max(X1) max(X2)]; %abscisse maximum
minX=[min(X1) min(X2)]; %abscisse minimum

maxY=[max(Y1) max(Y2)];%ordoonée maximum
minY=[min(Y1) min(Y2)]; %ordonnée minimum

%bord gauche
Dx1=[min(minX),min(minX)]; 
Dy1=[max(maxY),min(minY)];
%bord haut
Dx2=[min(minX),max(maxX)];
Dy2=[max(maxY),max(maxY)];
%bord droit
Dx3=[max(maxX),max(maxX)];
Dy3=[max(maxY),min(minY)];
%bord bas
Dx4=[min(minX),max(maxX)];
Dy4=[min(minY), min(minY)];

rB=15;
Z=0;

%La distance limite et changement d'angle minimum pour que ce soit un choc sont fixés

dmin=50;
alphamin=1;

%On calcule la distance entre les pucks
%Création d'un vecteur de booléens avec "true" si la distance est inférieure à dmin
%En multipliant par un vecteur d'indexes, on obtient un vecteur avec des index s'il y a un choc potentiel et zero s'il n'y en a pas

DistancePucks=sqrt((X1-X2).^2+(Y1-Y2).^2);
t=DistancePucks<dmin;
ConditionDistance=t.*(1:length(X1));

%Changement de direction
%Différence entre 2 éléments des vecteurs positions pour calculer la pente (tangente de l'angle par rapport à l'horizontale)
X1Diff=diff(X1);
Y1Diff=diff(Y1);
Angles1=atan2(Y1Diff,X1Diff);
X2Diff=diff(X2);
Y2Diff=diff(Y2);
Angles2=atan2(Y2Diff,X2Diff);

A=abs(diff(Angles1));
B=abs(diff(Angles2));

%On cherche les positions où à la fois le puck 1 et 2 ont une variation d'angle de plus de 1 radian
C=find(A>alphamin | B>alphamin); %opérateur logique "ou"

%Le vecteur C nous donne la position avant le changement de trajectoire, nous cherchons donc celle d'après: il faut l'incrémenter de 1

ConditionAngle=C+1;

%Le choc se produit si les deux conditions décrites sont satisfaites simultanément

ConditionChoc=intersect(ConditionAngle,ConditionDistance);

%On ne valide que les chocs  partir du 11e index afin d'éviter que le début ne soit interprété comme une succession de chocs (les pucks viennent d'être déposés sur la table)

choc=ConditionChoc(find(ConditionChoc>10));

%Détection des rebonds premier puck

%Bord droit
BD1=find((max(maxX)-X1)<=rB);
BD1(1+find(diff(BD1)==1))=[];

%Bord gauche
BG1=find((X1-min(minX))<=rB);
BG1(1+find(diff(BG1)==1))=[];

%Bord haut
BH1=find((Y1+rB)>=max(maxY));
BH1(1+find(diff(BH1)==1))=[];

%Bord bas
BB1=find((Y1-rB)<=min(minY));
BB1(1+find(diff(BB1)==1))=[];

%Détection des rebonds deuxième puck

%Bord droit
BD2=find((max(maxX)-X2)<=rB);
BD2(1+find(diff(BD2)==1))=[];

%Bord gauche
BG2=find((X2-min(minX))<=rB);
BG2(1+find(diff(BG2)==1))=[];

%Bord haut
BH2=find((Y2+rB)>=max(maxY));
BH2(1+find(diff(BH2)==1))=[];

%Bord bas
BB2=find((Y2-rB)<=min(minY));
BB2(1+find(diff(BB2)==1))=[];


fig=figure('Name','Air Hockey');
hold on

plot(Dx1,Dy1,'k',Dx2,Dy2,'k',Dx3,Dy3,'k',Dx4,Dy4,'k','linewidth',0.5);
axis([min(minX)-30 max(maxX)+50 min(minY)-60 max(maxY)+30]);

p1=plot(X1,Y1,'-o','markerfacecolor',[C2(1) C2(2) C2(3)]);
p2=plot(X2,Y2,'-o','markerfacecolor',[C3(1) C3(2) C3(3)]);
p1.Color=[C2(1) C2(2) C2(3)]; 
p2.Color=[C3(1) C3(2) C3(3)]; %on applique les couleurs choisies depuis Labview

scatter([X1(choc),X2(choc)],[Y1(choc),Y2(choc)],2000,'markerfacecolor','r','markeredgecolor','r','markerfacealpha',0.2,'linewidth',1); %choix des paramètres de "décoration" du point de choc entre les pucks
scatter(X1([BD1,BG1,BH1,BB1]),Y1([BD1,BG1,BH1,BB1]),400,'markeredgecolor',[C2(1) C2(2) C2(3)]);
scatter(X2([BD2,BG2,BH2,BB2]),Y2([BD2,BG2,BH2,BB2]),400,'markeredgecolor',[C3(1) C3(2) C3(3)]);

text((min(minX)+max(maxX))/2-30,max(maxY)+50,'Air Hockey','Color','black','FontSize',14,'FontWeight','bold');%affichage du titre
xlabel ('Largeur');
ylabel ('Hauteur');

text(30,max(maxY)+20,Seq); %Seq provient de LabView, c'est un string qui vaut soit 'Seq1m', soit 'Seq2m'
t=datetime('now');
text(30+60,max(maxY)+20,datestr(t)); %affichage de date et heure actuelles

str1="%i bands hit by puck 1";
txt1=length(BD1)+length(BG1)+length(BH1)+length(BB1);
legende1=sprintf(str1,txt1);

str2="%i bands hit by puck 2";
txt2=length(BD2)+length(BG2)+length(BH2)+length(BB2);
legende2=sprintf(str2,txt2);

str3="%i puck collision(s)";
txt3=length(choc);
legende3=sprintf(str3,txt3);

text(min(minX),min(minY)-15,legende1);%affichage du nombre de chocs entre puck1 et bandes
text(min(minX),min(minY)-25,legende2);%affichage du nombre de chocs entre puck2 et bandes
text(min(minX),min(minY)-35,legende3);%affichage du nombre de collisions entre pucks


hold off
saveas(fig,'AH_score','pdf') %sauvegarde du document PDF
%saveas est placé ici car dans le cas où l'on viendrait à fermer la fenêtre avant que le temps de valeur pause ne s'écoule, le fichier serait créé de toute façon

clear all
pause(10);


