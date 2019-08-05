FROM python:3.7.3-alpine
COPY . /opt/prob
WORKDIR /opt/prob
RUN pip3 install flask cyaron -i https://pypi.tuna.tsinghua.edu.cn/simple --no-cache
CMD ["python3", "judge.py"]