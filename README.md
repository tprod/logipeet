**LogiPEET**


- LogiPEET é um Projecto no âmbito da disciplina PEE.
- Para mais informações http://logipeet.web.ua.pt/ 

**API REST**

*Pré-requisitos*
1. Python 3.x
2. MySQL database

*Configurações*

No ficheiro yaml.

- **SQLALCHEMY_DATABASE_URI** Url da base de dados MySQL

esta configuração pode ser feita forçando a seguinte variável de ambiente SQLALCHEMY_DATABASE_URI, caso contrário alterar no ficheiro.

**Correr a Aplicação**

Requisitos de python:

`pip install -r requirements.txt`

Criar as tabelas

`flask db init`\
`flask db migrate`\
`flask db upgrade`

ou correr diretamente o script API/db/logipeet_db.sql na consola MySQL 

**Executar a API:**

`python app.py` ou `flask run`

