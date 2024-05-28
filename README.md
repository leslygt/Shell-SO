# ShellX
Eate projeto de sistemas operativos com a finalidae de criar um Shell. 

Foram implementadas as seguintes funcionalidades :

• Conversão de Imagem: Implementamos com sucesso a conversão de 
imagens de JPG para PNG.

• Pesquisa, Edição e Reexecução de Comandos Anteriores: Esta 
funcionalidade foi aprimorada para permitir uma usabilidade intuitiva e 
eficiente. É possível ver todo o histórico de comandos, selecionar um 
comando deste histórico, editá-lo ou reexecutá-lo.

• Gestor de Tarefas: O gestor de tarefas foi integrado ao ShellX, permitindo 
aos utilizadores, através de uma interface gráfica gerir tarefas diretamente 
do shellx, melhorando significativamente a interação com o sistema. O 
utilizador cria tarefas com título, descrição e prioridade, pode ver a lista de 
tarefas e editar as tarefas criadas

Como correr:

• make

• Para conversão: 
1. Instale o Imagemagick, aceda a https://legacy.imagemagick.org/script/download.php e siga as instruções de dowloand para o seu sistema operativo.
O imageMagick® is a free, open-source software suite, used for editing and manipulating digital images. It can be used to create, edit, compose, or convert bitmap images, and supports a wide range of file formats, including JPEG, PNG, GIF, TIFF, and Ultra HDR.
2. ./myapp convert [caminhodaimagem]
   
• Para o histórico: ./myapp history

• Para a gestão de tarefas: ./myapp task
