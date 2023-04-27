# Инструкции по развёртыванию системы

Cоздаём директории для хранения виртуальных дисков

```bash
sudo mkdir -p /mnt/vfs1
sudo mkdir -p /mnt/vfs2
```

Создаём файлы для виртуальных дисков размером 100 МБ

```bash
sudo dd if=/dev/zero of=vfs1.img bs=1M count=100
sudo dd if=/dev/zero of=vfs2.img bs=1M count=100
```

Создаём файловую систему ext4 на виртуальном диске

```bash
sudo mkfs.ext4 vfs1.img
sudo mkfs.ext4 vfs2.img
```

Монтируем виртуальные диски в директории vfs1 и vfs2

```bash
sudo mount -o loop vfs1.img /mnt/vfs1
sudo mount -o loop vfs2.img /mnt/vfs2
```

Копируем программы в директории

```bash
sudo cp ./server.c /mnt/vfs1
sudo cp ./client.c /mnt/vfs2
```

Переходим в нужную директорию

```bash
cd /mnt/vfs1
cd /mnt/vfs2
```
