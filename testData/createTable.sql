



create table yourtable2( a int, b char(10));



create table bank_accounts( 
    firstname char(30) not null,
    lastname  char(30) not null,
    birthday  date not null,
    birthplace char(30) not null,
    account_nr int primary key,
    balance    numeric(20,2) not null,
    constraint personCon unique(firstname, lastname, birthplace, birthday)
); 


drop table transactions;
create table transactions
(
    fromAccount int not null,
    toAccount   int not null,
    timestamp   TIMESTAMPTZ,
    amount      numeric(10,2),
    description char(100),
    tx_number   serial primary key,
    foreign key(fromAccount) references bank_accounts(account_nr),
    foreign key(toAccount) references bank_accounts(account_nr)
    
);

==========================================================================
Abfragen
========

select a.firstname, a.lastname, amount,b.firstname,b.lastname from transactions as t, bank_accounts as a, bank_accounts as b where t.fromAccount = a.account_nr and t.toAccount=b.account_nr;
