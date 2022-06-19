import random
import string
from typing import List, Tuple

import typer

LETTERS = string.ascii_letters
MIN_KEY_LENGTH = 1
MAX_KEY_LENGTH = 255
MIN_VALUE = 1
MAX_VALUE = (2**64) - 1
FILE_NAME = "tests.txt"


def generate_commands_lists(
    amount_of_data: int,
) -> Tuple[List[str], List[str], List[str]]:
    add_commands: List[str] = ['' for _ in range(amount_of_data)]
    search_commands: List[str] = ['' for _ in range(amount_of_data)]
    delete_commands: List[str] = ['' for _ in range(amount_of_data)]
    for i in range(amount_of_data):
        key = ''.join(
            random.choice(LETTERS) for i in range(random.randint(MIN_KEY_LENGTH, MAX_KEY_LENGTH))
        )
        value = random.randint(MIN_VALUE, MAX_VALUE)
        add_commands[i] = f'{key} {value}\n'
        search_commands[i] = f'{key}\n'
        delete_commands[i] = f'{key}\n'
    return add_commands, search_commands, delete_commands


def main(amount_of_data: int) -> None:
    add_commands, search_commands, delete_commands = generate_commands_lists(
        amount_of_data
    )
    with open(FILE_NAME, 'w') as file:
        file.write(str(f"{amount_of_data}\n"))
        lists = [add_commands, search_commands, delete_commands]
        for command_list in lists:
            for line in command_list:
                file.write(line)
        for command_list in lists:
            for line in command_list:
                file.write(line)


if __name__ == '__main__':
    typer.run(main)
