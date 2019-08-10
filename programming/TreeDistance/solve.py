import requests
import subprocess

ses = requests.session()

ses.get('http://judge.qwer.design:12354')
for i in range(200):
    ret = ses.get('http://judge.qwer.design:12354/api/decrease/'+str(i)).text
    if 'moectf' in ret:
        break
