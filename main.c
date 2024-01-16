import os
import cv2
import imageio
from tkinter import filedialog
from tkinter import Tk  # добавленный импорт

def create_video_from_images(image_folder, video_path, gif_path):
    images = [img for img in os.listdir(image_folder) if img.endswith(".jpg") or img.endswith(".png")]

    # Сортируем изображения в алфавитном порядке
    images.sort()

    # Определяем размеры изображений
    image_path = os.path.join(image_folder, images[0])
    img = cv2.imread(image_path)
    height, width, _ = img.shape

    # Инициализируем объект VideoWriter для создания видео
    video_writer = cv2.VideoWriter(video_path, cv2.VideoWriter_fourcc(*"mp4v"), 1, (width, height))

    # Создаем гиф-анимацию
    gif_images = []

    for image in images:
        image_path = os.path.join(image_folder, image)

        # Добавляем изображение в видео
        for _ in range(2):  # повторяем каждое изображение дважды (2 секунды на каждое)
            img = cv2.imread(image_path)
            video_writer.write(img)
            gif_images.append(img)  # добавляем изображение для гиф-анимации

    # Закрываем объект VideoWriter
    video_writer.release()

    # Создаем гиф-анимацию из списка изображений
    with imageio.get_writer(gif_path, duration=2, mode='I', loop=1, file=gif_path) as gif_writer:
        for img in gif_images:
            gif_writer.append_data(img)

if name == "main":
    root = Tk()
    root.withdraw()  # скрываем главное окно

    image_folder = filedialog.askdirectory(title="Выберите папку с фотографиями")
    video_path = "output_video.mp4"
    gif_path = filedialog.asksaveasfilename(defaultextension=".gif", filetypes=[("GIF files", "*.gif")])

    create_video_from_images(image_folder, video_path, gif_path)
    print(f"Видео создано: {video_path}")
    print(f"Гиф-анимация создана и сохранена: {gif_path}")
