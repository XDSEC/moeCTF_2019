import cyaron
import os
from flask import Flask, request, session, redirect
import random
import string

app = Flask(__name__)
app.secret_key = os.urandom(24)

data = {}
ans = {}
checked = {}


def generate_case():
    test_data = cyaron.IO(file_prefix="tree", data_id=session['token'])
    t = cyaron.Graph.tree(
        random.randint(1000, 10000)
    )
    session['queries'] = random.randint(2000, 20000)
    cnt_edges = len(t.edges)-1
    test_data.input_write(cnt_edges, session['queries'])
    test_data.input_writeln()
    test_data.input_writeln(t)
    data[session['token']] = []
    for i in range(session['queries']):
        query = (
            random.randint(0, cnt_edges),
            random.randint(0, cnt_edges)
        )
        test_data.input_writeln(query)
        data[session['token']].append(query)
    test_data.output_gen('./ans')
    ans[session['token']] = []
    with open('tree'+session['token']+'.out') as f:
        for i in f.readlines():
            ans[session['token']].append(i)
    os.remove('./tree'+session['token']+'.in')
    os.remove('./tree'+session['token']+'.out')
    ret = str(cnt_edges)+' '+str(session['queries'])+'\n'
    ret += t.to_str()+'\n'
    ret += str(data[session['token']][0][0])+' ' + \
        str(data[session['token']][0][1])+'\n'
    checked[session['token']] = False
    return ret


@app.route('/clear')
def clear():
    ans.clear()
    data.clear()
    checked.clear()


@app.route('/api/decrease/<index>')
def get_next(index):
    index = int(index)
    if 'token' not in session.keys():
        return '??what is this url???'
    session['queries'] = session['queries']-1
    if session['queries'] == 0:
        token = session['token']
        session.clear()
        data.pop(token)
        ans.pop(token)
        if checked[token]:
            return 'moectf{w0w_u_4re_r3ally_g00d_at_ACM}'
        else:
            return 'moectf{emmm...d1d_u_sk1p_s0mething?}'
    return str(data[session['token']][index+1][0])+' '+str(data[session['token']][index+1][1])+'\n'


@app.route('/', methods=["GET", "POST"])
def index():
    if request.method == 'GET':
        session['token'] = ''.join(random.sample(
            string.ascii_letters + string.digits, 8))
        return generate_case()
    elif request.method == 'POST':
        if 'token' not in session.keys():
            return 'please GET the input first'
        if 'ans' not in request.form.keys():
            return '''
please POST the answer in a form
for example: post('http://ip',data={'ans':your_answer})
'''
        index = len(data[session['token']])-session['queries']
        if int(request.form['ans']) != int(ans[session['token']][index]):
            session.clear()
            return 'wrong answer'
        checked[session['token']] = True
        return redirect('/api/decrease/'+str(index))


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=12354)
