<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="css/reset.css">
    <link rel="stylesheet" href="css/style.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Titan+One&display=swap" rel="stylesheet">
    <title>I'm too businesses panda</title>
</head>
<body>
<div class="content-wrapper">

    <!--  Main image  -->
    <? if (htmlspecialchars($_GET["lesson"]) == 1) { ?>

        <a href="/" title="Go to my main page, honey">
            <img src="img/page-1.jpg" alt="lesson one">
        </a>

    <? } elseif (htmlspecialchars($_GET["lesson"]) == 2) { ?>

        <a href="/" title="Go to my main page, honey">
            <img src="img/page-2.jpg" alt="lesson two">
        </a>

    <? } elseif (htmlspecialchars($_GET["lesson"]) == 3) { ?>

        <a href="/" title="Go to my main page, honey">
            <img src="img/page-3.jpg" alt="lesson three">
        </a>

    <? } else { ?>

        <a href="/" title="Go to my main page, honey">
            <img src="img/main-page.jpg" alt="Main lazy panda">
        </a>

    <? } ?>

    <!--  Text  -->
    <? if (htmlspecialchars($_GET["lesson"]) == 1) { ?>

        <h1>Laziness on a wood</h1>

        <h3>If you don't know how to relax at all, then this master class is for you! What could be more comfortable than a warm and round wood,
            which is easy to hug and ... be lazy...</h3>

    <? } elseif (htmlspecialchars($_GET["lesson"]) == 2) { ?>

        <h1>Laziness on the stone</h1>

        <h3>We have already shown you this wonderful world of laziness, and now let's try to relax on a cold stone...</h3>

    <? } elseif (htmlspecialchars($_GET["lesson"]) == 3) { ?>

        <h1>Master of Laziness</h1>

        <h3>You will think that this is the same as "Laziness on a wood", but look at this pose!
            This is a super level, to be lazy regardless of the conditions and state of mind!!!
            If you have already passed previous master classes or are confident in your level, welcome to the "Master of Laziness"!</h3>

    <? } else { ?>

        <h1>Hello!!! I'm Panda!!!</h1>

        <h2>I'm a lazy professional!<br> Here I can teach you my business!)</h2>

    <? } ?>

    <!-- Paginations   -->
    <nav class="paginator-wrapper">
        <a class="round-icon" href="?lesson=1">1</a>
        <a class="round-icon" href="?lesson=2">2</a>
        <a class="round-icon" href="?lesson=3">3</a>
    </nav>
</div>
</body>
</html>