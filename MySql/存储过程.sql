
CREATE TABLE IF NOT EXISTS article
(
    id BIGINT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT, -- primary key column
    auther_id BIGINT UNSIGNED NOT NULL,
    category_id BIGINT UNSIGNED NOT NULL,
    bview BIGINT UNSIGNED NOT NULL,
    comments BIGINT UNSIGNED NOT NULL,
    title VARCHAR(255) NOT NULL,
    content TEXT NOT NULL
);
INSERT INTO article(id,auther_id,category_id,bview,comments,title,content) VALUE(1,1,1,1,1,'1','1'),
(2,2,2,2,2,'2','2'),(3,1,1,3,3,'3','3');