<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js" type="text/javascript"></script>
        <style type="text/css">
            tr.header
            {
                font-weight:bold;
            }
            tr.alt
            {
                background-color: #777777;
            }
        </style>
        <script type="text/javascript">
            $(document).ready(function () {
                $('.striped tr:even').addClass('alt');
            });
        </script>
        <title></title>
    </head>
    <body>
        <?php
        $server = mysql_connect("localhost", "root", "password");
        $db = mysql_select_db("stocks", $server);
        $field = 'index';
        $sort = 'ASC';

        if (isset($_GET['sorting'])) {
            if ($_GET['sorting'] == 'ASC') {
                $sort = 'DESC';
            } else {
                $sort = 'ASC';
            }
        }
        if ($_GET['field'] == 'INDX') {
            $field = "INDX";
        } elseif ($_GET['field'] == 'COMPANY') {
            $field = "COMPANY";
        } elseif ($_GET['field'] == 'SYMBOL') {
            $field = "SYMBOL";
        } elseif ($_GET['field'] == 'VOLUME') {
            $field = "VOLUME";
        } elseif ($_GET['field'] == 'PRICE') {
            $field = "PRICE";
        } elseif ($_GET['field'] == 'CHG') {
            $field = "CHG";
        } elseif ($_GET['field'] == 'CHGPERCENT') {
            $field = "CHGPERCENT";
        }

        $query = "SELECT INDX, COMPANY, SYMBOL, VOLUME, PRICE, CHG, "
                . "CHGPERCENT FROM STOCKS) ORDER BY $field $sort";
        $result = mysql_query($sql) or die(mysql_error());
        echo'<table border="1">';
        echo'<th><a href="table1.php?sorting=' . $sort . '&field=INDX">Index:</a></th>
        <th><a href="table1.php?sorting=' . $sort . '&field=COMPANY">Company Name:</a></th>
        <th><a href="table1.php?sorting=' . $sort . '&field=SYMBOL">Company Symbol</a></th>
        <th><a href = "table1.php?sorting=' . $sort . '&field=VOLUME">Volume:</a></th>
        <th><a href = "table1.php?sorting=' . $sort . '&field=PRICE">Price:</a></th>
        <th><a href = "table1.php?sorting=' . $sort . '&field=CHG">Change:</a></th>
        <th><a href = "table1.php?sorting=' . $sort . '&field=CHGPERCENT">Change%:</a></th>';
        while ($row = mysql_fetch_array($result)) {
            echo'<tr><td>' . $row['INDX'] . '</td><td>' . $row['COMPANY'] . '</td><td>' . $row['SYMBOL']
            . '</td><td>' . $row['VOLUME'] . '</td><td>' . $row['PRICE'] . '</td><td>' . $row['CHG']
            . '</td><td>' . $row['CHGPERCENT'] . '</td></tr>';
        }
        echo'</table>';
        ?>
    </table>
</body>
</html>