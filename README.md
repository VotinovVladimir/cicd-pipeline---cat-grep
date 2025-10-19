## Basic CI/CD

### Part 1. Настройка **gitlab-runner**

Подними виртуальную машину *Ubuntu Server 22.04 LTS*.

![1757610026144](images/report/1757610026144.png)

![1757610086949](images/report/1757610086949.png)

```
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
sudo apt-get install gitlab-runner
```

Скачай и установи на виртуальную машину **gitlab-runner**.

![1757610745288](images/report/1757610745288.png)

Запусти **gitlab-runner** и зарегистрируй его для использования в текущем проекте (*DO6\_CICD*).

```
sudo gitlab-runner register
```

![1757610724159](images/report/1757610724159.png)

### Part 2. Сборка

В ветке **develop** cоздается файл *gitlab-ci.yml*, файл описывает процедуры CI/CD состоит из этапов: **build, style, test, deploy**.

![1757610947229](images/report/1757610947229.png)

##### Этап запуска сборки через мейк файл из проекта *Simple Bash*.

![1757613830374](images/report/1757613830374.png)

![1757614072419](images/report/1757614072419.png)

### Part 3. Тест кодстайла

Этап для **CI**, который запускает скрипт кодстайла (*clang-format*).

![1757614192766](images/report/1757614192766.png)

![1757616329958](images/report/1757616329958.png)

![1757616386662](images/report/1757616386662.png)

### Part 4. Интеграционные тесты

Этап запускается автоматически только при условии, если сборка и тест кодстайла прошли успешно *needs: - style - build*

![1757616677467](images/report/1757616677467.png)

![1757616904544](images/report/1757616904544.png)

![1757616926074](images/report/1757616926074.png)
