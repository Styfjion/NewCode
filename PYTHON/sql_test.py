from datetime import datetime

from sqlalchemy import create_engine, Table, MetaData, func, between, Column, Integer, String, DateTime, select
from sqlalchemy.orm import Session, sessionmaker, declarative_base

URL = 'mysql+pymysql://root:816921@172.19.250.218:3306/test'
ENGINE = create_engine(URL)

Base = declarative_base(ENGINE)


class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True, autoincrement=True)
    age = Column(Integer)
    name = Column(String(100))
    time = Column(DateTime, default=datetime.now())


class SqlTest(object):
    def __init__(self):
        self.db: Session = sessionmaker(bind=ENGINE)()
        self.meta_data = MetaData()

    def test(self):
        test_table = Table('test_table', self.meta_data, autoload=True, autoload_with=ENGINE)
        ret = self.db.query(func.IF(test_table.columns.count != 0,
                                    func.round(test_table.columns.salary / test_table.columns.count, 3), -1)
                            .label('avg')).all()
        print(list(map(lambda x: x._asdict(), ret)))
        ret2 = self.db.query(test_table).filter(between(test_table.columns.salary, 0, 2000)).all()
        print(ret2)
        self.db.close()

    @staticmethod
    def create():
        Base.metadata.create_all()

    def add_test(self):
        records = [User(age=11, name='test_name'), User(age=23, name='test-2')]
        self.db.add_all(records)
        self.db.commit()
        self.db.close()

    def query_batch_test_1(self):
        partitions_list = []
        for idx, row in enumerate(self.db.query(User.age, User.name).yield_per(3)):
            partitions_list.append(row._asdict())
            if (idx + 1) % 3 == 0:
                yield partitions_list
                partitions_list.clear()
        yield partitions_list

    def query_bach_test_2(self):
        fields = ['age', 'name']
        for partitions in self.db.execute(select(User.age, User.name).execution_options(yield_per=3)).partitions():
            yield [dict(zip(fields, partition)) for partition in partitions]

    def query_batch_test_3(self):
        partitions_list = []
        for idx, row in enumerate(self.db.execute(select(User.age, User.name).execution_options(yield_per=3))):
            partitions_list.append(row._asdict())
            if (idx + 1) % 3 == 0:
                yield partitions_list
                partitions_list.clear()
        yield partitions_list


if __name__ == '__main__':
    sql_test = SqlTest()
    for record in sql_test.query_batch_test_1():
        print(record)
    print('**********************************')
    for record in sql_test.query_bach_test_2():
        print(record)
    print('###################################')
    for record in sql_test.query_batch_test_3():
        print(record)
