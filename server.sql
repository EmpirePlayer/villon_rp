-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Хост: MySQL-5.7
-- Время создания: Дек 13 2024 г., 17:05
-- Версия сервера: 5.7.44
-- Версия PHP: 8.1.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `aheron`
--

-- --------------------------------------------------------

--
-- Структура таблицы `inviteCode`
--

CREATE TABLE `inviteCode` (
  `ID` int(11) NOT NULL COMMENT 'ID инвайт-кода',
  `userID` int(11) NOT NULL COMMENT 'ID аккаунта кто создал Инвайт-Код',
  `code` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Инвайт-код',
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Дата добавления инвайт-кода',
  `money` int(11) NOT NULL COMMENT 'Сколько денег дает'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Инвайт-Коды';

-- --------------------------------------------------------

--
-- Структура таблицы `playerLogs`
--

CREATE TABLE `playerLogs` (
  `ID` int(11) NOT NULL COMMENT 'ID лога',
  `type` int(2) NOT NULL COMMENT 'Тип лога',
  `userID` int(11) NOT NULL COMMENT 'ID акаунта от кого лог',
  `userIP` int(11) NOT NULL COMMENT 'IP при добавлении лога',
  `characterID` int(11) NOT NULL COMMENT 'ID персонажа от кого лог',
  `log` varchar(144) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Лог',
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Дата лога',
  `content_UserID` int(11) NOT NULL COMMENT 'ID аккаунта к которому было применено',
  `content_UserIP` int(11) NOT NULL COMMENT 'IP аккаунта к которому совершено действие',
  `content_CharacterID` int(11) NOT NULL COMMENT 'ID персонажа к которому применено'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Логи игроков';

-- --------------------------------------------------------

--
-- Структура таблицы `userCharacter`
--

CREATE TABLE `userCharacter` (
  `ID` int(11) NOT NULL COMMENT 'ID персонажа',
  `userID` int(11) NOT NULL COMMENT 'ID аккаунта',
  `Name` varchar(24) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Имя персонажа',
  `National` int(1) NOT NULL COMMENT 'Национальность персонажа',
  `Sex` int(1) NOT NULL COMMENT 'Пол персонажа',
  `Money` int(11) NOT NULL COMMENT 'Деньги персонажа',
  `Lvl` int(11) NOT NULL COMMENT 'Уровень персонажа',
  `Exp` int(11) NOT NULL COMMENT 'Опыт персонажа',
  `Age` int(2) NOT NULL COMMENT 'Возраст персонажа',
  `StyleChat` int(1) NOT NULL COMMENT 'Стиль разговора Персонажа',
  `Skin` int(3) NOT NULL COMMENT 'ID скина персонажа',
  `RegDateUnix` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Дата регистрации персонажа UNIX',
  `LastDateUnix` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Дата последнего входа персонажа UNIX'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Персонажи';

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `ID` int(11) NOT NULL COMMENT 'ID аккаунта',
  `Login` varchar(24) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Логин аккаунта',
  `Online` int(1) NOT NULL COMMENT 'Проверка на онлайн',
  `Password` varchar(66) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Пароль SHA',
  `Salt` varchar(11) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Пароль Соль',
  `RegdateUnix` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Дата регистрации UNIX',
  `Regip` int(11) NOT NULL COMMENT 'IP при регистрации',
  `LastdateUnix` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Последняя дата входа UNIX',
  `Lastip` int(11) NOT NULL COMMENT 'IP при последнем входе в игру',
  `InviteCode` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Инвайт-Код игрока'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Аккаунты';

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `inviteCode`
--
ALTER TABLE `inviteCode`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `inviteCode_id_fk_1` (`userID`);

--
-- Индексы таблицы `playerLogs`
--
ALTER TABLE `playerLogs`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `playerLogs_id_fk_1` (`userID`);

--
-- Индексы таблицы `userCharacter`
--
ALTER TABLE `userCharacter`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `character_id_fk_1` (`userID`);

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `inviteCode`
--
ALTER TABLE `inviteCode`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID инвайт-кода';

--
-- AUTO_INCREMENT для таблицы `playerLogs`
--
ALTER TABLE `playerLogs`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID лога';

--
-- AUTO_INCREMENT для таблицы `userCharacter`
--
ALTER TABLE `userCharacter`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID персонажа', AUTO_INCREMENT=28;

--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID аккаунта';

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `inviteCode`
--
ALTER TABLE `inviteCode`
  ADD CONSTRAINT `inviteCode_id_fk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `playerLogs`
--
ALTER TABLE `playerLogs`
  ADD CONSTRAINT `playerLogs_id_fk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `userCharacter`
--
ALTER TABLE `userCharacter`
  ADD CONSTRAINT `character_id_fk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
