from asyncio import tasks

from jinja2.runtime import identity

from datetime import datetime, timedelta

class TaskManager:
    def __init__(self):
        self.tasks = []

    def add_task(self, task):
        self.tasks.append(task)

    def make_sep(self):
        for _ in range(256):
            print("_", end = "")
        print()

    def show_tasks(self):
        if not self.tasks:
            print("Список задач пуст")

        for index, task in enumerate(self.tasks, start=1):
            self.make_sep()
            print(f"Задача: {index}",
                  f"Заголовок: {task.title}",
                  f"Описание задачи: {task.description}",
                  f"Статус: {task.status}",
                  f"Дата добавления: {task.date}",
                  f"Дедлайн: {task.deadline}",
                  sep = "\n"
                  )
            self.make_sep()



class Task:
    def __init__(self, title, description, status, date, deadline):
        self.title = title
        self.description = description
        self.status = status
        self.date = date
        self.deadline = deadline




class Menu:
    def __init__(self, task_manager):
        self.task_manager = task_manager
        self.actions = {
            '1': "Добавить задачу",
            '2': "Показать список задач",
            '3': "Изменить статус задачи",
            '4': "Удалить задачу",
            '5': "Выйти"
        }

    def show_actions(self):
        for (key,value) in self.actions.items():
            print(f"{key}. {value}")

    def identify_status(self):
        print("Статус (1 - выполнено, 2 - не выполнено, любая клавиша - свой статус)")
        choice = input("Статус: ")
        if choice == "1":
            status = "Выполнено"
        elif choice == "2":
            status = "Не выполнено"
        else:
            status = input(">> Введите личный статус: ")
        return status

    def identify_date(self):
        print("Дата добавления(1 - текущая дата, любая клавиша - своя дата): ")
        date_choice = input(">> ")
        if date_choice == "1":
            date = f"{datetime.now().date()} (Время: {datetime.now().strftime("%H:%M")})"
        else:
            date = input(">> Ваша дата: ")
        return date

    def set_deadline(self, added_date):
        while True:
            print("Дедлайн(1 - смещения от даты добавления, любая клавиша - дата пользователя)")
            show_date_choice = input(">> ")
            if show_date_choice == "1":
                print("Сколько дней вы даете на выполнение задачи?")
                user_input_days = int(input(">> "))
                try:
                    data_obj = datetime.strptime(added_date, "%Y-%m-%d (Время: %H:%M)")
                    new_date_obj = data_obj + timedelta(days=user_input_days)
                    date = f"{new_date_obj.date()} (Время: {new_date_obj.strftime("%H:%M")})"
                    return date
                except ValueError:
                    print("Невозможно прибавить дни к текущей дате")
            else:
                date = input("Введите дату: ")
                return date



    def get_task_titles(self):
        for index, self.task in enumerate(self.task_manager.tasks, start=1):
            print(f"{self.task.title} - {index}")


    def choice(self, action):
        if action in self.actions:
            print(f">> Вы выбрали: {self.actions[action]}")

            if action == '1':
                title = input("Заголовок задачи: ")
                description = input("Описание задачи: ")

                status = self.identify_status()

                date = self.identify_date()

                deadline = self.set_deadline(date)

                new_task = Task(title, description, status, date, deadline)
                self.task_manager.add_task(new_task)
                print(">> Задача успешно добавлена!")

            elif action == '2':
                self.task_manager.show_tasks()

            elif action == '3':
                print("Статус какой задачи вы желаете изменить?")
                self.get_task_titles()
                while True:
                    try:
                        status_change_choice = int(input(">> "))
                        break
                    except ValueError:
                        print("Введите корректный номер статуса")

                if status_change_choice <= len(self.task_manager.tasks):
                    self.task_manager.tasks[status_change_choice - 1].status =  self.identify_status()
                    print(f"Статус задачи '{self.task_manager.tasks[status_change_choice - 1].title}' успешно изменен")
                else:
                    print("Нет задачи с таким номером")

            elif action == '4':
                self.get_task_titles()
                print("Какую задачу вы хотите удалить?")
                while True:
                    try:
                        task_to_delete = int(input(">> "))
                        break
                    except ValueError:
                        print("Введите корректный номер задачи")

                if task_to_delete <= len(self.task_manager.tasks):
                    print(f"Задача '{self.task_manager.tasks[task_to_delete - 1].title}' успешно удалена")
                    self.task_manager.tasks.pop(task_to_delete-1)
                else:
                    print("Нет задачи с таким номером")


            elif action == '5':
                print("Выход...")
                return False
        else:
            print("Неизвестная команда. Попробуйте снова.")

        return True




def main():
    task_manager = TaskManager()
    menu = Menu(task_manager)
    while True:
        print("Выберите действие:")
        menu.show_actions()
        user_action = input("Введите номер: ")
        if not menu.choice(user_action):
            break


if __name__ == '__main__':
    main()
